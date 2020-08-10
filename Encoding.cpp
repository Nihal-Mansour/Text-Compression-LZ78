#include <fstream>
#include <string>
#include <iterator>
#include <unordered_map>
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
	mybinarydata bindata;
	fstream encodedfile("EncodedFile.bin", ios::binary | ios::in | ios::out | ios::trunc);
	char ch;
	int num;
	string str_ch = "";
	string temp = "";
	string prevcode = "";
	unordered_map <string, int> EncodedMap;
	int counter = 1;
	fstream filecontent;
	filecontent.open("enwik8");
	filecontent.get(ch);
	str_ch += ch;
	EncodedMap.insert(pair<string, int>(str_ch, counter++));
	bindata.setdata(0, ch);
	encodedfile.write((char *)& bindata, sizeof(mybinarydata));
	while (filecontent.get(ch)) {
		temp += ch;
		// the string is found in the map
		if (EncodedMap.find(temp) != EncodedMap.end()) {
			while (filecontent.get(ch)) {
				prevcode += temp;
				temp += ch;
				if (EncodedMap.find(temp) != EncodedMap.end()) {
					num = EncodedMap[temp];
					prevcode = "";
					continue;
				}
				else {
					num = EncodedMap[prevcode];
					EncodedMap.insert(pair<string, int>(temp, counter++));
					bindata.setdata(num, ch);
					encodedfile.write((char *)& bindata, sizeof(mybinarydata));
					temp = "";
					prevcode = "";
					break;
				}
			}
		}
		// the string not found in the map
		else {
			EncodedMap.insert(pair<string, int>(temp, counter++));
			bindata.setdata(0, ch);
			encodedfile.write((char *)& bindata, sizeof(mybinarydata));
			temp = "";
		}
		if (temp != "") {
			num = EncodedMap[temp];
			char empty = ' ';
			bindata.setdata(num, empty);
			encodedfile.write((char *)& bindata, sizeof(mybinarydata));
		}
	}
	
	filecontent.close();
	encodedfile.close();
	return 0;
}