#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <math.h>
#include <map>
#include <regex>
#include <tuple>
#include <stack>
using namespace std;

#define MAXpoint 1000000000
#define MINpoint 0
#define MAXcod 100
#define MINcod 1
#define MAXn 2500
#define MINn 1

   class Dreptunghi {
     public:
     int x1, y1, x2, y2, codC;
     double area;

         Dreptunghi (int X1, int Y1, int X2, int Y2, double AREA, int ccodC) {
      if (X1 < X2) {
        x1 = X1; x2 = X2;
      } else {
       x2 = X1; x1 = X2;
      }
      if (Y1 < Y2) {
        y1 = Y1; y2 = Y2;
      }
      else {
        y2 = Y1; y1 = Y2;
      }
      area = AREA;
      codC = ccodC;
    }
    };


    int nr = 0;
    vector <Dreptunghi> v;

    fstream fin;
    fstream fout;

void Meniu()
{
   cout << "===================================================== \n";
   cout << " \t\tMENIU \t \n ";
   cout << "===================================================== \n";
   cout << " 1. Afisarea datelor despre dreptunghi. (din fisier) \n";
   cout << " 2. Adaugare dreptunghi\n";
   cout << " 3. Stergerea unui dreptunghi dupa colturile acestuia. (din fisier)\n";
   cout << " 4. Construirea unui dreptunghi de arie minimala. \n";
   cout << " 5. Aria totala acoperita de terenurile in studiu.\n";
   cout << " 6. Culoarea care acopera cea mai mare suprafata din toate terenurile \n";
   cout << " 7. Transcrierea liniilor in fisierul ColColumn dupa o anumita culoare. \n";
   cout << " 8. Sortarea crescatoare a liniilor dupa codul culorii. \n";
   cout << " 9. Afisarea rezultatului problemei 8. \n";
}


double findArea(int x1, int y1, int x2, int y2) {

 return (x2 - x1) * (y2-y1);

}

void displayData() {

  int i = 1;
  cout << "\nAi selectat afisarea dreptunghiurilor: \n";
  for (vector<Dreptunghi>::iterator it = v.begin() ; it != v.end(); ++it) {
    cout << "Dreptunghiul " << i <<  ": " << (*it).x1 << " " << (*it).y1 << " " << (*it).x2 << " " << (*it).y2 << " " << (*it).codC << ", aria = " << (*it).area << endl;
    i++;
  }

}



bool isNumericPoint (string const &str) {
  if (regex_match(str, regex("[0-9]+"))) {
    int number = stoi(str);
    if (number <= MAXpoint && number >= MINpoint) {
        return true;
    }
  }
  return false;
}

bool isNumericCod(string const &str) {
    if (regex_match(str, regex("[0-9]+"))) {
    int number = stoi(str);
    if (number <= MAXcod && number >= MINcod) {
        return true;
    }
  }
  return false;
}

void limitMessage() {
   cout << "Introdu doar cifre, si respecta limita!" << endl;
}

tuple<int, int, int, int, int> citireDreptunghi(bool is) {

 string xx1, xx2, yy1, yy2, ccod;
 int cod;
restart:
 bool ok = false;
 cout << "x1: "; cin>>xx1;
 while (!isNumericPoint(xx1)) {
    limitMessage();
    cout << "x1: "; cin>>xx1;
    isNumericPoint(xx1);
 }

 int x1 = stoi(xx1);

 cout << "y1: "; cin>>yy1;
 while (!isNumericPoint(yy1)) {
    limitMessage();
    cout << "y1: "; cin>>yy1;
    isNumericPoint(yy1);
 }

 int y1 = stoi(yy1);
 cout << "x2: "; cin>>xx2;

 while (!isNumericPoint(xx2)) {
    limitMessage();
    cout << "x2: "; cin>>xx2;
    isNumericPoint(xx2);
 }
 int x2 = stoi(xx2);
 cout << "y2: "; cin>>yy2;

 while (!isNumericPoint(yy2)) {
    limitMessage();
    cout << "y2: "; cin>>yy2;
    isNumericPoint(yy2);
 }
 int y2 = stoi(yy2);

 if (!is) {
 cout << "Codul culoarei: "; cin>>ccod;

 while (!isNumericCod(ccod)) {
    limitMessage();
    cout << "Codul culoarei: "; cin>>ccod;
    isNumericCod(ccod);
 }
  cod = stoi(ccod);
 }

 if (!is) {
 for (auto it = v.begin(); it!=v.end(); it++) {
    if (it->x1 > x2 && it->x2 > x1 || it->y1 > y2 && it->y2 < y1 && it->codC == cod) {
        ok = true;
    }
 }

 if (ok == true) {
        cout << "-> Acest teren este ocupat, scrieti altul." << endl;
    goto restart;
 }
 else return {x1, y1, x2, y2, cod};
 }

  return {x1, y1, x2, y2, cod};
}

void addRectangle () {

 ofstream infile;
 infile.open("terenIn.txt", ios::out | ios::app);
 cout << "\nAi selectat adaugarea unui dreptunghi nou in fisier: " << endl;

 double area;

 auto [x1, y1, x2, y2, cod] = citireDreptunghi(false);

 area = (y2 - y1) * (x2 - x1);

 v.push_back({x1, y1, x2, y2, area, cod});
 infile << x1 << " " << y1 << " " << x2 << " " << y2 << " " << cod << endl;
 cout << "Dreptunghiul a fost inscris in fisier cu succes!" << endl;
 cout << endl;
 infile.close();
}

void deleteRectangle() {
 ofstream infile;
 infile.open("terenIn.txt", ios::out);
 cout << "\nAi selectat excluderea unui dreptunghi din fisier.\n";

 auto [x1, y1, x2, y2, cod] = citireDreptunghi(true);
 bool ok = false;

 //stergerea din lista;

 for (auto it = v.begin(); it != v.end(); it++) {
    if (it->x1 == x1 && it->y1 == y1 && it->x2 == x2 && it->y2 == y2) {
       it = v.erase(it);
       ok = true;
        break;
    }
 }
         if (ok == true) {
                //stergerea din fisier
            cout << "\nElementul a fost exclus.";
             for (vector<Dreptunghi>::iterator it = v.begin(); it != v.end(); ++it) {
          infile << (*it).x1 << " " << (*it).y1 << " " << (*it).x2 << " " << (*it).y2 << " " << (*it).codC << endl;
         }
           infile.close();
         }
         else {
            cout << "\nNu exista un astfel de dreptunghi.";
         }
}

void newFileByColor() {

ofstream infile("ColComun.txt");
cout << "\nAi selectat crearea unui fisier cu liniile a codului culorii tastat: \n";
short int cod;
cout << "Codul: "; cin>>cod;
bool ok = false;

for (auto it = v.begin(); it!=v.end(); it++) {
    if (it->codC == cod) {
        infile << it->x1 << " " << it->y1 << " " << it->x2 << " " << it->y2 << " " << it->codC << endl;
        ok = true;
    }
}

if (ok) {
    cout << "\nDatele au fost inscrise cu succes in fisierul creat.";
}
else cout << "\nNu exista un astfel de cod.";

}

///Parametrul-functie pentru a sorta datele dupa codul culorii

bool is_bigger(const Dreptunghi& x, const Dreptunghi& y) {

  return x.codC < y.codC;

}

void sortByColor() {

ofstream infile("terenIn.txt", ios::out);

sort(v.begin(), v.end(), is_bigger);

for (auto it = v.begin(); it!=v.end(); it++) {
 infile << it->x1 << " " << it->y1 << " " << it->x2 << " " << it->y2 << " " << it->codC << endl;
}

cout << "\nCodurile culorilor au fost sortate!\n";

}

void totalArea() {

 cout << "\n Ati selectat aria totala a dreptunghiurilor.\n";

 double area;


 for (auto it = v.begin(); it!=v.end(); it++) {
    area = area + it->area;
 }

 cout << "\n -> Aria totala acoperita: " << area << endl;

}

int maxHistogram(vector<int>& heights)
    {
        heights.push_back(0);
        int n = heights.size();
        stack<int> st;
        int res = 0;

        int i = 0;
        while(i < n)
        {
            if(st.empty() || heights[i] >= heights[st.top()])
              st.push(i++);
            else
             {
                 int top = st.top();
                 st.pop();
                 res = max(res, heights[top] * (st.empty() ? i : i - st.top() - 1));
             }
        }

        return res;
    }

int maximalRectangle(vector<vector<int>>& matrix)
    {
        if(matrix.empty())
            return 0;

        int m = matrix.size();
        int n = matrix[0].size();
        int res = 0;

        vector<int> height(n, 0);
        for (int k = 0; k<v.size(); k++) {
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(matrix[i][j] == v[k].codC)
                    height[j]++;
                else
                    height[j] = 0;
            }

            res = max(res, maxHistogram(height));
        }
        }
        return res;
    }

void biggestColorArea() {

 cout << "\nAti selectat afisarea culoarei care acopera cea mai mare suprafata din toate terenurile.\n";

 vector<int> cods;
 for (auto it = v.begin(); it!=v.end(); it++) {
    cods.push_back(it->codC);
 }

 map<int, int> colorMax;

 sort(cods.begin(), cods.end());
 cods.erase(unique(cods.begin(), cods.end()), cods.end());

  for (auto it = cods.begin(); it!=cods.end(); it++) {
        double area = 0;
    for (auto itt = v.begin(); itt!=v.end(); itt++) {
        if (*it == itt->codC) {
            area = area + itt->area;
        }
    }
    colorMax.insert(std::pair<int, int>(*it, area));
  }

 auto x = max_element(colorMax.begin(), colorMax.end(),
                      [](const pair<int, int>& p1, const pair<int, int>& p2) {
                       return p1.second < p2.second;
                      });

 cout << "Culoarea: " << x->first << ", aria = " << x->second << endl;

}

bool isEmpty() {

 if (v.size() == 0) {
    return true;
 }

 return false;

}

tuple <int, int, int, int> newRectangleByMinArea() {

vector <pair<int, int>> minValue;
vector <pair<int, int>> maxValue;

for (auto it=v.begin(); it!=v.end(); it++) {
  minValue.push_back(make_pair(it->x1, it->y1));
  maxValue.push_back(make_pair(it->x2, it->y2));
}

auto xMax = max_element(maxValue.begin(),
            maxValue.end(),
            [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; });

auto yMax = max_element(maxValue.begin(),
            maxValue.end(),
            [](const auto& lhs, const auto& rhs) { return lhs.first < rhs.first; });


auto xMin = min_element(minValue.begin(),
            minValue.end(),
            [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; });


auto yMin = min_element(minValue.begin(),
            minValue.end(),
            [](const auto& lhs, const auto& rhs) { return lhs.first< rhs.first; });

cout << "Dreptunghiul minimal ce acopera tot teritoriul: [" << yMin->first << ", " << xMin->first << ", " << yMax->first << ", " << xMax->second << "]" << endl;

 return {yMin->first, xMin->first, yMax->first, xMax->second};
}

void displayResult() {

ofstream infile("terenOut.txt", ios::out);

  auto [x1, y1, x2, y2] = newRectangleByMinArea();

  vector<vector<int>> M(y2, vector<int>(x2));

/// Completarea matricei cu dreptunghiurile prezente si cu culorile acesteia

  for (auto &s : v) {
    for (int i = s.y1; i<s.y2; i++) {
        for (int j = s.x1; j<s.x2; j++) {
            M[i][j] = s.codC;
        }
    }
  }

  for (int i = M.size()-1; i>=0; i--) {
    for (int j = 0; j<M[1].size(); j++) {
        cout << M[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
  cout << maximalRectangle(M) << endl;
  infile << maximalRectangle(M) << endl;

  }

int main () {

/// Citirea datelor

 ifstream infile;
 infile.open("terenIn.txt", ios::in);
 int x1, x2, x3, x4, y1, y2, y3, y4, cod;
 int xc, yc; ///Centrul punctului
 int xd, yd; ///Diagonala injumatatita
 double area;

 if (infile.fail()) {
    throw runtime_error("Fisierul nu a putut fi gasit.");
 }

 while (infile.is_open() && !infile.eof()) {
    infile >> x1 >> y1 >> x2 >> y2 >> cod;
    if (x1>MAXpoint || y1>MAXpoint || x2>MAXpoint || y2>MAXpoint) {
        throw runtime_error("Punctul scris trece de limita 1000000000.");
    }
    if (x1<MINpoint || y1<MINpoint || x2<MINpoint || y2<MINpoint) {
        throw runtime_error("Punctul scris este mai mic de 0.");
    }
    if (cod>MAXcod) {
        throw runtime_error("Codul culorii trece de limita.");
    }
    if (cod<MINcod) {
        throw runtime_error("Codul este mai mic de 1");
    }
    area = (y2 - y1) * (x2 - x1);

    if (infile.eof()) {
        break;
    }
    v.push_back({x1, y1, x2, y2, area, cod});
 }

 //infile.close();

/// Meniul
Meniu();
int option;
string confirm;

do {
    cout << "Alege optiunea (1-8): \n";
    cin>>option;

    switch(option) {

    case 1: displayData(); break;
    case 2: addRectangle(); break;
    case 3: deleteRectangle(); break;
    case 4: newRectangleByMinArea(); break;
    case 5: totalArea(); break;
    case 6: biggestColorArea(); break;
    case 7: newFileByColor(); break;
    case 8: sortByColor(); break;
    case 9: displayResult(); break;
    default: cout << "Invalid!!!"; break;
    }
    cout << "\nApasa y sau Y pentru a continua: ";
    cin>>confirm;
}
while(confirm == "y" || confirm == "Y");
return 0;
}
