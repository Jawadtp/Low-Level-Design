#include <iostream>
#include <vector>

using namespace std;

class NotificationChannel
{
    public:
        virtual void sendNotification(string message) = 0;
        virtual ~NotificationChannel() = default;
};

class SMS: public NotificationChannel
{
    public:
        void sendNotification(string message) override
        {
            cout << "Sending SMS: " << message << endl; 
        }
};

class Email: public NotificationChannel
{
    public:
        void sendNotification(string message) override
        {
            cout << "Sending email: " << message << endl;
        }
};

class NotificationService
{
    private:
        vector<NotificationChannel*> observers;
    
    public:
        NotificationService(vector<NotificationChannel*> observers): observers(observers){}

        void sendNotification(string message)
        {
            for(auto &observer: observers)
                observer->sendNotification(message);
        }
};

int main()
{
    NotificationChannel* channel1 = new SMS();
    NotificationChannel* channel2 = new Email();
    vector<NotificationChannel*> channels{channel1, channel2};
    NotificationService* notificationService = new NotificationService(channels);
    notificationService->sendNotification("test notif");
    return 0;
}