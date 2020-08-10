#include <fstream>
#include <string>
#include <iterator>
#include <map>
#include <vector>
using namespace std;

class mybinarydata {
private:
	int value;
	char code;
public:
	mybinarydata() {}
	~mybinarydata() {}
	void setdata(int val , char c) {
		this->value = val;
		this->code = c;
	}
	int getvalue() {
		return this->value;
	}
	char getcode() {
		return this->code;
	}
};

int main() {
    vector <pair<int, string>> DecodedMap;
	map <int, string> CreatedMap;
	int decodedcounter = 1;
    fstream encodedfile("EncodedFile.bin", ios::binary | ios::in | ios::out);
	encodedfile.seekg(0);
	mybinarydata readdata;
	while (encodedfile.read((char *)& readdata, sizeof(mybinarydata))) {
		string str = "";
		str += readdata.getcode();
		DecodedMap.push_back(make_pair(readdata.getvalue(), str));
	}
	for (auto it = DecodedMap.begin(); it != DecodedMap.end(); ++it) {
		if (it->first == 0) {
			CreatedMap.insert(pair<int, string>(decodedcounter++, it->second));
		}
		else {
			auto i = CreatedMap.find(it->first);
			string s = i->second;
			s += it->second;
			CreatedMap.insert(pair<int, string>(decodedcounter++, s));
		}
	}
	ofstream decodedfile("DecodedFile.txt");
	for (auto it = CreatedMap.begin(); it != CreatedMap.end(); ++it) {
		decodedfile << it->second;
	}

    encodedfile.close();
	decodedfile.close();
	return 0;
}