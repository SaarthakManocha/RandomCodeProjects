#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

map<string, float> gradePoints = {
    {"S", 10}, {"A", 9}, {"B", 8},
    {"C", 7}, {"D", 6}, {"E", 5}, {"F", 0}
};

struct Subject {
    string name;
    float credits;
};

map<int, vector<Subject>> semesterData = {
    {1, {
        {"Linear Algebra and Calculus", 4}, {"Optics and Semiconductor Physics", 3},
        {"Programming using C", 3}, {"English", 2},
        {"Physics Lab", 1.5}, {"English Lab", 1}, {"C Programming Lab", 1.5},
        {"Engineering Graphics", 2.5}, {"Digital Fabrication Workshop", 1.5}
    }},
    {2, {
        {"Differential Equations and Numerical Methods", 4}, {"Chemistry", 3},
        {"Basic Electrical Engineering", 3}, {"Data Structures using C++", 3},
        {"Chemistry Lab", 1.5}, {"Community Engagement", 1},
        {"Data Structures Lab", 1}, {"Robotics and Drones Lab", 2.5}, {"BEE Lab", 1}
    }},
    {3, {
        {"DC Circuits and Sensors", 3}, {"Digital Logic and Computer Architecture", 3},
        {"Design Thinking", 2}, {"Discrete Mathematics", 3},
        {"Java Programming", 3}, {"Design and Analysis of Algorithms", 3},
        {"Java Programming Lab", 1}, {"DAA Lab", 1}, {"Moocs/Internship", 2}
    }},
    {4, {
        {"Probability and Queueing Theory", 4}, {"EDA and Visualization", 3},
        {"Database Management Systems", 3}, {"Operating Systems", 3},
        {"Engineering Economics and Accountancy", 3}, {"Environmental Science", 0},
        {"Professional Elective - I", 3},
        {"DBMS Lab", 1}, {"OS Lab", 1}, {"EDA Lab", 1},
        {"Mini Project - I", 1}, {"Up Skill Certification I", 0.5}
    }},
    {5, {
        {"Software Engineering", 3}, {"Enterprise App Development", 3},
        {"Machine Learning", 3}, {"Computer Networks", 3},
        {"FLAT", 3}, {"Professional Elective - II", 3},
        {"CASE Tools Lab", 1}, {"EAD Lab", 1}, {"CN Lab", 1},
        {"ML Lab", 1}, {"Competitive Coding", 1}, {"Internship II", 2}
    }},
    {6, {
        {"Big Data Analytics", 3}, {"Embedded Systems and IoT", 3},
        {"Deep Learning", 3}, {"Compiler Design", 3},
        {"UHV II", 1}, {"Artificial Intelligence", 3},
        {"Professional Elective - III", 3},
        {"BDA Lab", 1}, {"IoT Lab", 1}, {"DL Lab", 1},
        {"Mini Project II", 1}, {"Employability Skills", 1}, {"Up Skill Certification II", 0.5}
    }},
    {7, {
        {"Professional Elective - IV", 3}, {"Professional Elective - V", 3},
        {"Professional Elective - VI", 3}, {"Open Elective - I", 3},
        {"PE Lab", 1}, {"Project Part I", 2}
    }},
    {8, {
        {"Open Elective - II", 3}, {"Open Elective - III", 3},
        {"Technical Seminar", 1}, {"Project Part II", 4}
    }}
};

void showProgressBar(float percentage) {
    cout << "GPA Progress: [";
    int ticks = percentage * 10;
    for (int i = 0; i < 10; ++i) {
        cout << (i < ticks ? "=" : " ");
    }
    cout << "] " << fixed << setprecision(2) << percentage * 10 << "/10\n";
}

void motivate(float gpa) {
    if (gpa == 10)
        cout << "\U0001F389 Legend Mode Activated! You're on FIRE! \U0001F525\n";
    else if (gpa >= 9)
        cout << "\u2728 Excellent job! Almost a 10-pointer genius!\n";
    else if (gpa >= 8)
        cout << "\U0001F44F Great! Keep pushing, you're almost there!\n";
    else if (gpa >= 6)
        cout << "\U0001F44D Good effort! Next time, aim higher!\n";
    else
        cout << "\U0001F4AA Don't give up! Every genius has a comeback story.\n";
}

int main() {
    int sem;
    cout << "Enter your semester (1-8): ";
    cin >> sem;

    if (semesterData.find(sem) == semesterData.end()) {
        cout << "Semester data not found.\n";
        return 1;
    }

    vector<Subject> subjects = semesterData[sem];
    float totalCredits = 0, weightedSum = 0;

    cout << "Do you have the grade for each subject? (y/n)\n";

    float knownCredits = 0, knownWeightedSum = 0;
    float unknownCredits = 0;

    for (auto& sub : subjects) {
        char hasGrade;
        cout << "Do you have grade for \"" << sub.name << "\"? (y/n): ";
        cin >> hasGrade;
        hasGrade = tolower(hasGrade);

        if (hasGrade == 'y') {
            string grade;
            cout << "Enter grade (S/A/B/...) for \"" << sub.name << "\" (Credits: " << sub.credits << "): ";
            cin >> grade;
            for (char &c : grade) c = toupper(c);
            if (gradePoints.find(grade) == gradePoints.end()) {
                cout << "Invalid grade.\n";
                return 1;
            }
            knownWeightedSum += gradePoints[grade] * sub.credits;
            knownCredits += sub.credits;
        } else {
            unknownCredits += sub.credits;
        }
    }

    if (unknownCredits == 0) {
        float gpa = knownWeightedSum / knownCredits;
        cout << "\n\U0001F393 Your GPA: " << fixed << setprecision(2) << gpa << " / 10.00\n";
        showProgressBar(gpa / 10.0);
        motivate(gpa);
        return 0;
    }

    float targetGPA;
    cout << "Enter your target GPA for semester " << sem << ": ";
    cin >> targetGPA;

    if (targetGPA > 10 || targetGPA < 0) {
        cout << "Invalid GPA target.\n";
        return 1;
    }

    float requiredWeightedSum = targetGPA * (knownCredits + unknownCredits) - knownWeightedSum;
    float requiredGrade = requiredWeightedSum / unknownCredits;

    cout << fixed << setprecision(2);
    cout << "\nYour current GPA with known grades: " << (knownCredits > 0 ? (knownWeightedSum / knownCredits) : 0) << "\n";
    cout << "To achieve your target GPA of " << targetGPA << ",\n";

    if (requiredGrade > 10) {
        cout << "Sorry, you need an average grade POINT of " << requiredGrade << " in remaining subjects,\nwhich is impossible (max is 10).\n";
        cout << "Time to pull an all-nighter or adjust your target GPA!\n";
    } else if (requiredGrade < 0) {
        cout << "Wow, you have already surpassed the target GPA!\nNo pressure on remaining subjects.\n";
    } else {
        cout << "You need an average grade POINT of " << requiredGrade << " in the remaining subjects.\n";
        
        // Plain table output
        cout << "\nGrade  | Grade Point | New GPA    | Status\n";
        cout << "---------------------------------------------\n";

        bool possible = false;
        for (auto it = gradePoints.rbegin(); it != gradePoints.rend(); ++it) {
            float testGPA = (knownWeightedSum + it->second * unknownCredits) / (knownCredits + unknownCredits);
            cout << setw(6) << left << it->first << " | "
                 << setw(11) << it->second << " | "
                 << setw(9) << fixed << setprecision(2) << testGPA << " | ";
            if (testGPA >= targetGPA) {
                cout << "Achieves Target\n";
                possible = true;
            } else {
                cout << "Below Target\n";
            }
        }
        if (!possible) {
            cout << "\nNo single grade in all remaining subjects can reach your target GPA.\n";
            cout << "Time to pull an all-nighter or adjust your target GPA!\n";
        }
    }
    return 0;
}
