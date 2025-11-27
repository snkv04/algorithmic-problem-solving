#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Spell { 
    private:
        string scrollName;
    public:
        Spell(): scrollName("") { }
        Spell(string name): scrollName(name) { }
        virtual ~Spell() { }
        string revealScrollName() {
            return scrollName;
        }
};

class Fireball : public Spell { 
    private: int power;
    public:
        Fireball(int power): power(power) { }
        void revealFirepower(){
            cout << "Fireball: " << power << endl;
        }
};

class Frostbite : public Spell {
    private: int power;
    public:
        Frostbite(int power): power(power) { }
        void revealFrostpower(){
            cout << "Frostbite: " << power << endl;
        }
};

class Thunderstorm : public Spell { 
    private: int power;
    public:
        Thunderstorm(int power): power(power) { }
        void revealThunderpower(){
            cout << "Thunderstorm: " << power << endl;
        }
};

class Waterbolt : public Spell { 
    private: int power;
    public:
        Waterbolt(int power): power(power) { }
        void revealWaterpower(){
            cout << "Waterbolt: " << power << endl;
        }
};

class SpellJournal {
    public:
        static string journal;
        static string read() {
            return journal;
        }
}; 
string SpellJournal::journal = "";

void counterspell(Spell *spell) {

  if (Fireball *casted = dynamic_cast<Fireball*>(spell)) {
    casted->revealFirepower();
  } else if (Frostbite *casted = dynamic_cast<Frostbite*>(spell)) {
    casted->revealFrostpower();
  } else if (Thunderstorm *casted = dynamic_cast<Thunderstorm*>(spell)) {
    casted->revealThunderpower();
  } else if (Waterbolt *casted = dynamic_cast<Waterbolt*>(spell)) {
    casted->revealWaterpower();
  } else {
    auto lcs = [](const string &a, const string &b) {
        int lena = a.size(), lenb = b.size();
        vector<vector<int>> mem(lena+1, vector<int>(lenb+1, 0));
        for (int i = 1; i <= lena; ++i) {
            for (int j = 1; j <= lenb; ++j) {
                mem[i][j] = max(mem[i-1][j], mem[i][j-1]);
                if (a[i-1] == b[j-1]) {
                    mem[i][j] = max(mem[i][j], mem[i-1][j-1] + 1);
                }
            }
        }
        return mem[lena][lenb];
    };
    
    cout << lcs(SpellJournal::read(), spell->revealScrollName()) << endl;
  }

}

class Wizard {
    public:
        Spell *cast() {
            Spell *spell;
            string s; cin >> s;
            int power; cin >> power;
            if(s == "fire") {
                spell = new Fireball(power);
            }
            else if(s == "frost") {
                spell = new Frostbite(power);
            }
            else if(s == "water") {
                spell = new Waterbolt(power);
            }
            else if(s == "thunder") {
                spell = new Thunderstorm(power);
            } 
            else {
                spell = new Spell(s);
                cin >> SpellJournal::journal;
            }
            return spell;
        }
};

int main() {
    int T;
    cin >> T;
    Wizard Arawn;
    while(T--) {
        Spell *spell = Arawn.cast();
        counterspell(spell);
    }
    return 0;
}
