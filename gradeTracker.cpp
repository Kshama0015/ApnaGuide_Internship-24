#include <iostream> 
#include <string> 
#include <vector> 
#include <algorithm>
using namespace std; 

class Learner { 
  private: 
    string fullName; 
    string classLevel;
    int idNumber; 
    double score; 

  public:
    Learner(const string &name, const string &level, int id, double marks)
        : fullName(name), classLevel(level), idNumber(id), score(marks) {}


    double getScore() const {
      return score;
    }

    // to calculate the grade based on marks
    string determineGrade() {
      if (score >= 90) {
        return "A+";
      } else if (score >= 80) {
        return "A";
      } else if (score >= 70) {
        return "B";
      } else if (score >= 60) {
        return "C";
      } else if(score>=50) {
        return "D";
      }else 
        return "F";
    }

    // display learner information
    void showDetails() {
      std::cout << "\n\nName: " << fullName << endl; 
      std::cout << "Class: " << classLevel << endl; 
      std::cout << "ID Number: " << idNumber << endl; 
      std::cout << "Score: " << score << endl; 
      std::cout << "Grade: " << determineGrade() << endl; 
    }
};

class GradeTracker { 
  private:
    vector<Learner> learners; 

  public:
    void addLearner(const Learner &learner) {
      learners.push_back(learner);
    }

    void showTopLearners() const {
      if (learners.size() < 3) {
        std::cout << "Learners are less than 3" << endl;
        return;
      }

      vector<Learner> sortedLearners = learners;
      sort(sortedLearners.begin(), sortedLearners.end(), [](const Learner &a, const Learner &b) {
        return a.getScore() > b.getScore();
      });

      std::cout << "\nTop 3 Learners: " << endl;
      for (int i = 0; i < 3; ++i) {
        sortedLearners[i].showDetails();
      }
    }
};

int main() {
  GradeTracker tracker; 
  int numberOfLearners;
  
  std::cout << "Enter the number of learners: ";
  std::cin >> numberOfLearners;
  std::cin.ignore(); 

  for (int i = 0; i < numberOfLearners; ++i) {
    string name; 
    string level; 
    int id; 
    double marks; 

    std::cout << "\nEnter details for learner " << (i + 1) << ":";
    std::cout << "\nName: "; 
    std::getline(std::cin, name); 
    std::cout << "Class: "; 
    std::getline(std::cin, level); 

    std::cout << "ID Number: "; 
    std::cin >> id; 

    std::cout << "Score (0-100): "; 
    std::cin >> marks; 
    std::cin.ignore(); 
    Learner learner(name, level, id, marks); 
    tracker.addLearner(learner); 
  }

  // Display top 3 learners
  tracker.showTopLearners();

  return 0; 
}


                                             // THANKYOU //