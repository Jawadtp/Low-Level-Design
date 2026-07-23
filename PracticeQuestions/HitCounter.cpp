#include <iostream>
#include <vector>
#include <shared_mutex>
#include <mutex>

using namespace std;

class HitStorage
{
    public:
        virtual void recordHit(int second) = 0;
        virtual int getHits(int currTime) = 0;
        virtual ~HitStorage() = default;
};

class HitStorageArrayBased: public HitStorage
{
    private:
        vector<int> hitsAtSecond;
        vector<int> lastHitTimestamp;
        int k;
        vector<shared_mutex*> mutexes;
    public:
        HitStorageArrayBased(int k)
        {
            hitsAtSecond = vector<int>(k,0);
            lastHitTimestamp = vector<int>(k,-1);
            this->k = k;
            for(int i=0; i<k; i++)
                mutexes.push_back(new shared_mutex());
        }

        // In prod., second will be generated on the server side.
        void recordHit(int second) override
        {
            int slot = second%k;

            unique_lock<shared_mutex> lock(*mutexes[slot]);

            if(lastHitTimestamp[slot]!=second)
            {
                lastHitTimestamp[slot] = second;
                hitsAtSecond[slot] = 0;
            }
            hitsAtSecond[slot]++;
        }

        // In prod., currTime will be generated on the server side.
        int getHits(int currTime) override
        {
            int hits = 0;
            int slot = currTime%k;


            for(int i=0; i<k; i++)
            {
                shared_lock<shared_mutex> lock(*mutexes[i]);

                if(currTime - lastHitTimestamp[i] < k)
                    hits+=hitsAtSecond[i];
            }

            return hits;
        }
};

class HitManagementService
{
    private:
        HitStorage* hitStorage;

    public:
        HitManagementService(HitStorage* hitStorage): hitStorage(hitStorage){}

        void recordHit(int second)
        {
            hitStorage->recordHit(second);
        }

        int getHits(int currTimestamp)
        {
            return hitStorage->getHits(currTimestamp);
        }
};

int main()
{
    HitStorage* hitStorage = new HitStorageArrayBased(3);
    HitManagementService hitManager = HitManagementService(hitStorage);
    hitManager.recordHit(0);
    hitManager.recordHit(1);
    hitManager.recordHit(1);
    hitManager.recordHit(1);
    hitManager.recordHit(2);
    hitManager.recordHit(6);
    cout << hitManager.getHits(3);
    return 0;
}