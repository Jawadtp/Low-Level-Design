#include <iostream>
#include <vector>

using namespace std;

class WeatherObserver
{
    public:
        virtual void receiveUpdate(double temp) = 0;
        virtual ~WeatherObserver() = default;
};

class TVChannel: public WeatherObserver
{
    private:
        string channelName;
    
    public:
        TVChannel(string channelName): channelName(channelName){}

        void receiveUpdate(double temp) override
        {
            cout << "Weather update on channel " << channelName <<": " << "temp: " << temp << endl;
        }
};

class Phone: public WeatherObserver
{
    private:    
        string model;
        string userName;
    public:
        Phone(string model, string name): model(model), userName(name){}

        void receiveUpdate(double temp) override
        {
            cout << "Weather update [" << model << " " << userName << "]: " << temp << endl; 
        }
};

class WeatherStation
{
    private:
        double temp;
        vector<WeatherObserver*> observers;

        void notifyObservers()
        {
            for(auto &observer: observers)
            {
                observer->receiveUpdate(temp);
            }
        }

    public:
        WeatherStation(vector<WeatherObserver*> observers): observers(observers){}

        void updateTemp(double temp)
        {
            this->temp = temp;
            notifyObservers();
        }

};

int main()
{
    WeatherObserver* obs1 = new Phone("OnePlus 13", "Jawad");
    WeatherObserver* obs2 = new TVChannel("Asianet");
    WeatherStation weatherStation = WeatherStation({obs1, obs2});
    weatherStation.updateTemp(27.0);
    return 0;
}