#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <map>
using namespace std;

struct HuffChar{
	char ch;
	int weight;
	HuffChar* lc;HuffChar*rc;HuffChar* prt;

	HuffChar(char c,int w):ch(c),weight(w){};
};

bool operator< (HuffChar const& hc1,HuffChar const& hc2){return hc1.weight > hc2.weight;}
bool operator==(HuffChar const& hc1,HuffChar const& hc2){return hc1.weight == hc2.weight;}
priority_queue<HuffChar*> pq; //huffchars ranked according to frequency(weight)
map <char,int> ch_frqc;
map <char,int>::iterator it;

void naiveCopy(string inputFilename, string outputFilename) {
	ofstream ofs(outputFilename.c_str(), ios::out | ios::binary);
	ifstream ifs(inputFilename.c_str(), ios::in | ios::binary);
	char c;
	while (ifs.get(c)){
		if(ch_frqc.find(c)!=ch_frqc.end())
			ch_frqc[c]++;
		else 
			ch_frqc[c]=1;
	//	ofs.put(c);
	}
	for(it=ch_frqc.begin();it!=ch_frqc.end();it++){
		HuffChar* hc=new HuffChar(it->first,it->second);
		pq.push(hc);
	}
	while(pq.size()>1){
		HuffChar* a=pq.top();pq.pop();
		HuffChar* b=pq.top();pq.pop();
		HuffChar* sum=new HuffChar('^',a->weight+b->weight);
		pq.push(sum);
	}
	ofs.close();
	ifs.close();
}

void compress(string inputFilename, string outputFilename) {
	naiveCopy(inputFilename, outputFilename);
};

void decompress(string inputFilename, string outputFilename) {
	naiveCopy(inputFilename, outputFilename);
}

void useage(string prog) {
	cerr << "Useage: " << endl
		<< "    " << prog << "[-d] input_file output_file" << endl;
	exit(2);
}

int main(int argc, char* argv[]) {
	int i;
	string inputFilename, outputFilename;
 
  
	bool isDecompress = false;
	for (i = 1; i < argc; i++) {
		if (argv[i] == string("-d")) isDecompress = true;
		else if (inputFilename == "") inputFilename = argv[i];
			else if (outputFilename == "") outputFilename = argv[i];
				else useage(argv[0]);
	}
	if (outputFilename == "") useage(argv[0]);
	if (isDecompress) decompress(inputFilename, outputFilename);
	else compress(inputFilename, outputFilename);
	return 0;
}
