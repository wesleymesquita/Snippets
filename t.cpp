#include<vector>
#include<string>

using namespace std;

 struct ohlc {
        vector<unsigned int> timestamp;
        vector<float> open;
        vector<float> high;
        vector<float> low;
        vector<float> close;
        vector<float> volume;
    } ;


ohlc *read_csv(string file_name) {
    // open file and read stuff
    static ohlc ohlc;
    int read_value;
	ohlc.timestamp.push_back(read_value);
    return &ohlc;
}

int sim(ohlc* ohlc) {
    // do stuff
    return 1;
}


main() {
    std::string input_file;
	ohlc *ohlc = read_csv(input_file);
    int results = sim(ohlc);
}