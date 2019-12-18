#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

const int GROUP_COUNT = 4;

struct pupil {
    string name;
    float avgGrade;
};

struct groups {
    pupil group[30];
};

int findLineCount(const char filename[]);
void readPupils(pupil Pupils[], int pupilCount, const char filename[]);
float getGroupAverageGrade(pupil Pupils[], int pupilCount);
bool comparePupils(pupil PupilOne, pupil PupilsTwo);
void sortPupils(pupil Pupils[], int pupilCount);
int getGoodPupilCount(pupil Pupils[], int pupilCount, float groupAverageGrade);
void joinGoodPupils(pupil TopPupils[], int topPupilCount, pupil Groups[], int groupsCount, int topPupilsCounts[]);

int main() {
    const char groupOne[] = "duom3_1.txt",
               groupTwo[] = "duom3_2.txt",
               groupThree[] = "duom3_3.txt",
               groupFour[] = "duom3_4.txt";

    int groupOneCount = findLineCount(groupOne),
        groupTwoCount = findLineCount(groupTwo),
        groupThreeCount = findLineCount(groupThree),
        groupFourCount = findLineCount(groupFour);


    pupil PupilsGroupOne[groupOneCount],
          PupilsGroupTwo[groupTwoCount],
          PupilsGroupThree[groupThreeCount],
          PupilsGroupFour[groupFourCount];

    groups Groups[GROUP_COUNT];

    readPupils(PupilsGroupOne, groupOneCount, groupOne);
    readPupils(PupilsGroupTwo, groupTwoCount, groupTwo);
    readPupils(PupilsGroupThree, groupThreeCount, groupThree);
    readPupils(PupilsGroupFour, groupFourCount, groupFour);

    float groupOneAvg = getGroupAverageGrade(PupilsGroupOne, groupOneCount),
          groupTwoAvg = getGroupAverageGrade(PupilsGroupTwo, groupTwoCount),
          groupThreeAvg = getGroupAverageGrade(PupilsGroupThree, groupThreeCount),
          groupFourAvg = getGroupAverageGrade(PupilsGroupFour, groupFourCount);

    sortPupils(PupilsGroupOne, groupOneCount);
    sortPupils(PupilsGroupTwo, groupTwoCount);
    sortPupils(PupilsGroupThree, groupThreeCount);
    sortPupils(PupilsGroupFour, groupFourCount);

    int goodPupilsGroupOneCount = getGoodPupilCount(PupilsGroupOne, groupOneCount, groupOneAvg),
        goodPupilsGroupTwoCount = getGoodPupilCount(PupilsGroupTwo, groupTwoCount, groupTwoAvg),
        goodPupilsGroupThreeCount = getGoodPupilCount(PupilsGroupThree, groupThreeCount, groupThreeAvg),
        goodPupilsGroupFourCount = getGoodPupilCount(PupilsGroupFour, groupFourCount, groupFourAvg);

    int topPupilsCounts[GROUP_COUNT] = {goodPupilsGroupOneCount, goodPupilsGroupTwoCount,
                                        goodPupilsGroupThreeCount, goodPupilsGroupFourCount};

    int topPupilsCount = goodPupilsGroupOneCount + goodPupilsGroupTwoCount +
                         goodPupilsGroupThreeCount + goodPupilsGroupFourCount;

    Groups[0].group = PupilsGroupOne;

    for(int i = 0; i < goodPupilsGroupOneCount; i++) {
        Groups[0].groups
    }

    pupil TopPupils[topPupilsCount];

//    TODO add groups to Groups



    return 0;
}

int findLineCount(const char filename[])
{
    ifstream in(filename);
    int n = 0;
    string line;
    while(!in.eof()) {
        getline(in, line);
        n++;
    }
    in.close();

    return n;
}

void readPupils(pupil Pupils[], int pupilCount, const char filename[])
{
    ifstream in(filename);

    for(int i = 0; i < pupilCount; i++) {
        in >> Pupils[i].name >> Pupils[i].avgGrade;
    }

    in.close();
}

float getGroupAverageGrade(pupil Pupils[], int pupilCount)
{
    float sum = 0;

    for(int i = 0; i < pupilCount; i++) {
        sum += Pupils[i].avgGrade;
    }

    return sum/pupilCount;
}

void sortPupils(pupil Pupils[], int pupilCount)
{
    sort(Pupils, Pupils + pupilCount, comparePupils) ;
}

bool comparePupils(pupil PupilOne, pupil PupilsTwo)
{
    bool pupilIsBetter = false;

    if (PupilOne.avgGrade > PupilsTwo.avgGrade) {
        pupilIsBetter = true;
    }

    return pupilIsBetter;
}

int getGoodPupilCount(pupil Pupils[], int pupilCount, float groupAverageGrade)
{
    int count = 0;

    for(int i = 0; i < pupilCount; i++) {
        count++;
        if (Pupils[i].avgGrade < groupAverageGrade) {
            break;
        }
    }

    return  count;
}

void joinGoodPupils(pupil TopPupils[], int topPupilCount, pupil Groups[], int groupsCount, int topPupilsCounts[])
{
    int topCount = 0;
    for(int i = 0; i < groupsCount; i++) {
        for(int j = 0; j < topPupilsCounts[i]; j++ ) {
            TopPupils[topCount].name = Groups[i].name;
        }
    }
}