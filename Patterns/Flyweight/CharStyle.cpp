#include <iostream>
#include <unordered_map>
#include <mutex>

using namespace std;

class CharacterStyle
{
    private:
        int size;
        string font;
        string color;
    
    public:
        CharacterStyle(int size, string font, string color): size(size), font(font), color(color){}

        void display(char value)
        {
            cout << "Displaying " << value << " in " << font << ", " << color << ", size " << size << endl;
        }
};

class Character
{
    private:
        char value;
        CharacterStyle* characterStyle;
    
    public:
        Character(char value, CharacterStyle *characterStyle): value(value), characterStyle(characterStyle){}

        void displayChar()
        {
            characterStyle->display(value);
        }
};

class CharacterStyleMap
{
    private:
        unordered_map<string, CharacterStyle*> styleMap;
        mutex mtx;
        CharacterStyleMap(){
            cout << "Char style map singleton initiated" << endl;
        }

    public:
        static CharacterStyleMap& getInstance()
        {
            static CharacterStyleMap styleMap;
            return styleMap;
        }



        CharacterStyle* getCharacterStyle(int size, string font, string color)
        {
            string key = to_string(size) + "#" + font + "#" + color;
            CharacterStyle* style = nullptr;
            lock_guard<mutex> lock(mtx);
            if(styleMap.count(key)==0)
            {
                styleMap[key] = new CharacterStyle(size, font, color);
                cout << "Created new char style" << endl;
            }
            return styleMap[key];
        }
};

int main()
{
    CharacterStyleMap& styleMap = CharacterStyleMap::getInstance();
    Character *A = new Character('A', styleMap.getCharacterStyle(2, "arial", "blue"));
    Character *B = new Character('B', styleMap.getCharacterStyle(2, "arial", "blue"));
    A->displayChar();
    B->displayChar();
    return 0;
}