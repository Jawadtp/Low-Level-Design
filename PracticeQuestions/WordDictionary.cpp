#include <iostream>
#include <vector>
#include <shared_mutex>
#include <mutex>

using namespace std;

class Trie
{
   
    public:
        vector<Trie*> children;
        bool isEnd;
        string meaning;

        Trie()
        {
            children = vector<Trie*>(26, nullptr);
            isEnd = false;
            meaning = "";
        }
        
        ~Trie()
        {
            for(auto &child: children)
                delete child;
        }

        string getMeaning()
        {
            return this->meaning;
        }

        void addWord(string word, string meaning)
        {

            Trie* curr = this;

            for(char &c: word)
            {
                c = tolower(c);
                if(curr->children[c-'a']==nullptr)
                    curr->children[c-'a'] = new Trie();
                curr = curr->children[c-'a'];
            }

            curr->isEnd = true;
            curr->meaning = meaning;
        }

        string getMeaning(string word)
        {
            Trie* curr = this;

            for(char &c: word)
            {
                c = tolower(c);
                if(curr->children[c-'a']==nullptr) return "";
                curr = curr->children[c-'a'];
            }

            if(curr->isEnd==true) return curr->meaning;

            return "";
        }
};

class Dictionary
{
    private:
        Trie* dictStorage;
        shared_mutex mtx;

    public:
        Dictionary()
        {
            dictStorage = new Trie();
        }

        ~Dictionary(){
            delete dictStorage;
        }

        void addWord(string word, string meaning)
        {
            unique_lock<shared_mutex> lock(mtx);
            dictStorage->addWord(word, meaning);
        }

        string getMeaning(string word)
        {
            shared_lock<shared_mutex> lock(mtx);
            return dictStorage->getMeaning(word);
        }

};

int main()
{
    cout << "Dictionary \n";
    Dictionary dict;
    dict.addWord("Apple", "red fruit");
    dict.addWord("car", "vehicle");
    cout << dict.getMeaning("car") << endl;
    cout << dict.getMeaning("apple") << endl;
    cout << dict.getMeaning("bike") << endl;

    return 0;
}