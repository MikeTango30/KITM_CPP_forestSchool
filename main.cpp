#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;

const int GROUP_COUNT = 4;
const int MAX_PUPIL_COUNT = 30;

const string GROUP_ONE = "duom3_1.txt",
        GROUP_TWO = "duom3_2.txt",
        GROUP_THREE = "duom3_3.txt",
        GROUP_FOUR = "duom3_4.txt",
        OUTPUT_FILE = "rez3.txt",
        SEPARATOR = "------------------";

struct pupil {
    string name;
    float avgGrade;
};

struct groups {
    pupil pupils[MAX_PUPIL_COUNT];
    float groupAverage;
    int pupilCount;
    int topPupilCount;
    string groupName;
};

int findLineCount(string filename);

void setPupilCounts(groups Groups[], string Filenames[]);

void readPupils(groups Groups[], string Filenames[]);

void setGroupNames(groups Groups[], string groupName);

void getAverages(groups Groups[]);

bool comparePupils(pupil PupilOne, pupil PupilTwo);

void sortPupils(groups Groups[]);

void getTopPupilCount(groups Groups[]);

void aggregateTopPupils(groups Groups[]);

void writeResults(groups Groups[]);

int main() {
    string Filenames[GROUP_COUNT] = {GROUP_ONE, GROUP_TWO, GROUP_THREE, GROUP_FOUR},
            groupName = "Klase";
    groups Groups[GROUP_COUNT + 1]; //+1 place for top group

    setPupilCounts(Groups, Filenames);
    readPupils(Groups, Filenames);
    setGroupNames(Groups, groupName);
    getAverages(Groups);
    sortPupils(Groups);
    getTopPupilCount(Groups);
    aggregateTopPupils(Groups);
    writeResults(Groups);

    return 0;
}

int findLineCount(string filename) {
    ifstream in(filename.c_str());
    int n = 0;
    string line;
    while (!in.eof()) {
        getline(in, line);
        n++;
    }
    in.close();

    return n;
}

void setPupilCounts(groups Groups[], string Filenames[]) {
    for (int i = 0; i < GROUP_COUNT; i++) {
        Groups[i].pupilCount = findLineCount(Filenames[i]);
    }

}

void readPupils(groups Groups[], string Filenames[]) {
    for (int i = 0; i < GROUP_COUNT; i++) {
        ifstream in(Filenames[i].c_str());

        for (int j = 0; j < Groups[i].pupilCount; j++) {
            in >> Groups[i].pupils[j].name >> Groups[i].pupils[j].avgGrade;
        }

        in.close();
    }
}

void setGroupNames(groups Groups[], string groupName) {
    for (int i = 0; i < GROUP_COUNT; i++) {
        Groups[i].groupName = groupName + " " + to_string(i + 1);
    }
}

void getAverages(groups Groups[]) {
    for (int i = 0; i < GROUP_COUNT; i++) {
        float sum = 0;
        for (int j = 0; j < Groups[i].pupilCount; j++) {
            sum += Groups[i].pupils[j].avgGrade;
        }
        Groups[i].groupAverage = sum / Groups[i].pupilCount;
    }
}

bool comparePupils(pupil PupilOne, pupil PupilTwo) {
    bool pupilIsBetter = false;

    if (PupilOne.avgGrade > PupilTwo.avgGrade) {
        pupilIsBetter = true;
    }

    return pupilIsBetter;
}

void sortPupils(groups Groups[]) {
    for (int i = 0; i < GROUP_COUNT; i++) {
        sort(Groups[i].pupils, Groups[i].pupils + Groups[i].pupilCount, comparePupils);
    }
}

void getTopPupilCount(groups Groups[]) {
    for (int i = 0; i < GROUP_COUNT; i++) {
        int count = 0;
        for (int j = 0; j < Groups[i].pupilCount; j++) {
            if (Groups[i].pupils[j].avgGrade < Groups[i].groupAverage) {
                break;
            }
            count++;
        }
        Groups[i].topPupilCount = count;
    }
}

// function does too many things
void aggregateTopPupils(groups Groups[]) {
    int topCountIndex = 0,
            bestOfBestCount = 0,
            topGroupIndex = GROUP_COUNT;
    float sum = 0;

    // join top pupils
    for (int i = 0; i < GROUP_COUNT; i++) {
        for (int j = 0; j < Groups[i].topPupilCount; j++) {
            Groups[topGroupIndex].pupils[topCountIndex].name = Groups[i].pupils[j].name;
            Groups[topGroupIndex].pupils[topCountIndex].avgGrade = Groups[i].pupils[j].avgGrade;
            sum += Groups[topGroupIndex].pupils[topCountIndex].avgGrade;
            topCountIndex++;
        }
    }

    // set top Count
    Groups[topGroupIndex].pupilCount = topCountIndex;

    // set top Average
    Groups[topGroupIndex].groupAverage = sum / Groups[topGroupIndex].pupilCount;

    // sort top Pupils
    sort(Groups[topGroupIndex].pupils, Groups[topGroupIndex].pupils + Groups[topGroupIndex].pupilCount, comparePupils);

    // set best of top Count
    for (int i = 0; i < Groups[topGroupIndex].pupilCount; i++) {
        if (Groups[topGroupIndex].pupils[i].avgGrade < Groups[topGroupIndex].groupAverage) {
            break;
        }
        bestOfBestCount++;
    }
    Groups[topGroupIndex].topPupilCount = bestOfBestCount;
}

void writeResults(groups Groups[]) {
    ofstream out(OUTPUT_FILE.c_str());

    // write group data
    for (int i = 0; i < GROUP_COUNT; i++) {
        out << Groups[i].groupName << ":\n";
        for (int j = 0; j < Groups[i].topPupilCount; j++) {
            out << Groups[i].pupils[j].name << " " << fixed << setprecision(2) << Groups[i].pupils[j].avgGrade << '\n';
        }
        out << SEPARATOR << '\n';
    }

    // write top group data
    out << "Rezultatas:\n";
    for (int i = 0; i < Groups[GROUP_COUNT].topPupilCount; i++) {
        out << Groups[GROUP_COUNT].pupils[i].name << " "
            << fixed << setprecision(2) << Groups[GROUP_COUNT].pupils[i].avgGrade << '\n';
    }

    out.close();
}