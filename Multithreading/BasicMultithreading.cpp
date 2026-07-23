#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
mutex mtx;

void countTillN(int n)
{
    for(int i=0; i<n; i++)
    {
        this_thread::sleep_for(chrono::milliseconds(1));
        lock_guard<mutex> lock(mtx);
        cout << "Count: " << i << endl;
    }
}

int main()
{
    thread t1(countTillN, 100);
    thread t2(countTillN, 100);
    t1.join();
    t2.join();
    return 0;
}