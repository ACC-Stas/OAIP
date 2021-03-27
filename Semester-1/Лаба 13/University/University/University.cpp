#include <iostream>
#include <string>
#include <vector>


class University {
private:
	std::string name;

	struct Teacher {
	private: 
		std::string name;
	public:
		Teacher(std::string name = "No name") {
			this->name = name;
		}
		void changeName(std::string name) {
			this->name = name;
		}
		std::string getName() {
			return name;
		}
	};

	struct Subject {
	private:
		std::string name;
	public:
		std::vector<Teacher> teachers;

		Subject(std::string name) {
			this->name = name;
		}
		void changeName(std::string name) {
			this->name = name;
		}
		std::string getName() {
			return name;
		}
		void attachTeacher(std::string name) {
			Teacher teacher(name);
			teachers.push_back(teacher);
		}
	};

	struct Marks {
	private:
		std::string name;
	public:
		std::vector<int> marks;
		Marks(std::string name) {
			this->name = name;
		}
		std::string getName() {
			return name;
		}
		void pushMark(int mark) {
			marks.push_back(mark);
		}
		int getAverage() {
			int average = 0;
			for (int i = 0; i < marks.size(); i++) {
				average += marks[i];
			}
			if (marks.size() != 0) {
				average = average / marks.size();
			}
			return average;
		}
	};

	struct Student {
	private:
		std::string name;

	public:
		std::vector<Marks> marks;

		Student(std::string name = "Forgot name") {
			this->name = name;
		}
		void changeName(std::string name) {
			this->name = name;
		}
		std::string getName() {
			return name;
		}
		void giveMark(int mark, std::string subject) {
			bool hadMarks = false;
			for (int i = 0; i < marks.size(); i++) {
				if (marks[i].getName() == subject) {
					marks[i].pushMark(mark);
					hadMarks = true;
					break;
				}
			}
			if (!hadMarks) {
				Marks m(subject);
				m.pushMark(mark);
				marks.push_back(m);
			}
		}
	};

	struct Group {
	private:
		std::string name;
		std::string specialty;
	public:
		std::vector<Student> students;

		Group(std::string name = "No name", std::string specialty = "No info") {
			this->name = name;
			this->specialty = specialty;
		}
		void changeName(std::string name) {
			this->name = name;
		}
		void changeSpecialty(std::string specialty) {
			this->specialty = specialty;
		}
		std::string getName() {
			return name;
		}
		std::string getSpecialty() {
			return specialty;
		}
		void attachStudent(std::string name) {
			Student student(name);
			students.push_back(student);
		}
		void showCleverest() {
			bool isGood = true;
			for (int i = 0; i < students.size(); i++) {
				isGood = true;
				if (students[i].marks.size() < 3) {
					isGood = false;
				}
				for (int j = 0; j < students[i].marks.size(); j++) {
					if (students[i].marks[j].getAverage() < 8) {
						isGood = false;
					}
				}
				if (isGood) {
					std::cout << students[i].getName() << " - good one\n";
				}
			}
		}
	};

	struct Course {
	private:
		int number;
	public:
		std::vector<Group> groups;
		std::vector<Subject> subjects;

		Course(int number) {
			this->number = number;
		}
		int getNumber() {
			return number;
		}
		void attachGroup(std::string name = "No name", std::string specialty = "No info") {
			Group group(name, specialty);
			groups.push_back(group);
		}
		void attachSubject(std::string name) {
			Subject subject(name);
			subjects.push_back(name);
		}
		void showCleverest() {
			for (int i = 0; i < groups.size(); i++) {
				std::cout << groups[i].getName() << ":\n";
				groups[i].showCleverest();
			}
		}
	};

	struct Faculty {
	private:
		std::string name;
	public:
		std::vector<Course> courses;

		Faculty(std::string name = "No name") {
			this->name = name;
		}
		void changeName(std::string name) {
			this->name = name;
		}
		std::string getName() {
			return name;
		}
		void attachCourse(int number) {
			Course course(number);
			courses.push_back(number);
		}
		void showTeachers() {
			for (int i = 0; i < courses.size(); i++) {
				std::cout << courses[i].getNumber() << ":\n";
				for (int j = 0; j < courses[i].subjects.size(); j++) {
					std::cout << courses[i].subjects[j].getName() << ":\n";
					for (int k = 0; k < courses[i].subjects[j].teachers.size(); k++) {
						std::cout << courses[i].subjects[j].teachers[k].getName() << "\n";
					}
				}
			}
		}
	};

public:
	std::vector<Faculty> faculties;
	
	University(std::string name = "No name") {
		this->name = name;
	}
	void changeName(std::string name) {
		this->name = name;
	}
	std::string getName() {
		return name;
	}
	void attachFaculty(std::string nameOfFaculty) {
		Faculty faculty(nameOfFaculty);
		faculties.push_back(faculty);
	}
	void showFaculties() {
		for (int i = 0; i < faculties.size(); i++) {
			std::cout << faculties[i].getName() << "\n";
		}
	}
	void findStudent(std::string name) {
		bool findStudent = false;
		for (int i = 0; i < faculties.size(); i++) {
			for (int j = 0; j < faculties[i].courses.size(); j++) {
				for (int k = 0; k < faculties[i].courses[j].groups.size(); k++) {
					for (int f = 0; f < faculties[i].courses[j].groups[k].students.size(); f++) {
						if (name == faculties[i].courses[j].groups[k].students[f].getName()) {
							std::cout << name << " - " << faculties[i].getName() << " - " << faculties[i].courses[j].getNumber() << " - " <<
								faculties[i].courses[j].groups[k].getName() << "\n";
							findStudent = true;
						}
					}
				}
			}
		}
		if (!findStudent) {
			std::cout << name << " - no information in database\n";
		}
	}
	void showAllData() {
		for (int i = 0; i < faculties.size(); i++) {
			std::cout << faculties[i].getName() << ":\n";
			faculties[i].showTeachers();
			for (int j = 0; j < faculties[i].courses.size(); j++) {
				std::cout << faculties[i].courses[j].getNumber() << ":\n";
				faculties[i].courses[j].showCleverest();
				for (int k = 0; k < faculties[i].courses[j].groups.size(); k++) {
					std::cout << faculties[i].courses[j].groups[k].getName() << ":\n";
					for (int f = 0; f < faculties[i].courses[j].groups[k].students.size(); f++) {
						std::cout << faculties[i].courses[j].groups[k].students[f].getName() << ":\n";
						for (int g = 0; g < faculties[i].courses[j].groups[k].students[f].marks.size(); g++) {
							std::cout << faculties[i].courses[j].groups[k].students[f].marks[g].getName() << ": ";
							for (int z = 0; z < faculties[i].courses[j].groups[k].students[f].marks[g].marks.size(); z++) {
								std::cout << faculties[i].courses[j].groups[k].students[f].marks[g].marks[z] << " ";
							}
							std::cout << "\n";
						}
					}
				}
			}
		}
	}
};


int main()
{
	University BSUIR("BSR");
	std::cout << BSUIR.getName() << "\n";
	BSUIR.changeName("BSUIR");
	std::cout << BSUIR.getName() << "\n";
	BSUIR.attachFaculty("Faculty of Computer Systems Networks");

	std::cout << BSUIR.faculties[0].getName() << "\n";
	BSUIR.faculties[0].changeName("Faculty of Computer Systems and Networks");
	std::cout << BSUIR.faculties[0].getName() << "\n";
	BSUIR.attachFaculty("Faculty of Information Technology and Management");
	std::cout << BSUIR.faculties[1].getName() << "\n";
	std::cout << BSUIR.faculties[0].getName() << "\n";
	std::cout << "\n\n";
	BSUIR.attachFaculty("Faculty of Computer Engineering");
	BSUIR.attachFaculty("Faculty of Radio Engineering and Electronics");
	BSUIR.attachFaculty("Faculty of infocommunications");
	for (int i = 0; i < BSUIR.faculties.size(); i++) {
		std::cout << BSUIR.faculties[i].getName() << "\n";
	}

	std::cout << "\n";
	BSUIR.showFaculties();
	std::cout << "\n";
	BSUIR.faculties[0].attachCourse(1);
	BSUIR.faculties[0].attachCourse(2);
	BSUIR.faculties[0].attachCourse(3);
	BSUIR.faculties[0].attachCourse(4);

	BSUIR.faculties[0].courses[0].attachGroup("Hell walruses", "Spesialsts A");
	BSUIR.faculties[0].courses[0].attachGroup("Normalized", "Spesialsts B");
	std::cout << BSUIR.faculties[0].courses[0].groups[0].getName() << " - " << BSUIR.faculties[0].courses[0].groups[0].getSpecialty() << "\n";
	std::cout << BSUIR.faculties[0].courses[0].groups[1].getName() << " - " << BSUIR.faculties[0].courses[0].groups[1].getSpecialty() << "\n";
	std::cout << "\n";

	BSUIR.faculties[0].courses[0].groups[0].attachStudent("Wasyok number 1");
	BSUIR.faculties[0].courses[0].groups[0].attachStudent("Wasyok number 2");
	BSUIR.faculties[0].courses[0].groups[0].attachStudent("Wasyok number 3");
	std::cout << BSUIR.faculties[0].courses[0].groups[0].students[0].getName() << "\n";
	std::cout << BSUIR.faculties[0].courses[0].groups[0].students[1].getName() << "\n";
	std::cout << BSUIR.faculties[0].courses[0].groups[0].students[2].getName() << "\n";
	std::cout << "\n";

	BSUIR.faculties[0].courses[0].attachSubject("High speed lying on the couch");
	BSUIR.faculties[0].courses[0].attachSubject("Normal speed lying on the couch");
	BSUIR.faculties[0].courses[0].attachSubject("Low speed lying on the couch");
	BSUIR.faculties[0].courses[0].subjects[0].attachTeacher("Ilon Mask");
	BSUIR.faculties[0].courses[0].subjects[0].attachTeacher("Ivanov Ivan Ivanovich");
	std::cout << BSUIR.faculties[0].courses[0].subjects[0].getName() << " - " << BSUIR.faculties[0].courses[0].subjects[0].teachers[0].getName() <<
		" and " << BSUIR.faculties[0].courses[0].subjects[0].teachers[1].getName() << "\n";
	std::cout << "\n";

	BSUIR.faculties[0].showTeachers();
	std::cout << "\n";

	BSUIR.faculties[0].courses[0].groups[0].students[0].giveMark(10, "High speed lying on the couch");
	BSUIR.faculties[0].courses[0].groups[0].students[0].giveMark(9, "High speed lying on the couch");
	BSUIR.faculties[0].courses[0].groups[0].students[0].giveMark(10, "Normal speed lying on the couch");
	BSUIR.faculties[0].courses[0].groups[0].students[0].giveMark(10, "Low speed lying on the couch");

	BSUIR.faculties[0].courses[0].groups[0].students[1].giveMark(10, "High speed lying on the couch");
	BSUIR.faculties[0].courses[0].groups[0].students[1].giveMark(9, "High speed lying on the couch");
	BSUIR.faculties[0].courses[0].groups[0].students[1].giveMark(5, "Normal speed lying on the couch");
	BSUIR.faculties[0].courses[0].groups[0].students[1].giveMark(10, "Low speed lying on the couch");

	BSUIR.faculties[0].courses[0].groups[0].students[2].giveMark(10, "High speed lying on the couch");
	BSUIR.faculties[0].courses[0].groups[0].students[2].giveMark(9, "High speed lying on the couch");
	BSUIR.faculties[0].courses[0].groups[0].students[2].giveMark(10, "High speed lying on the couch");
	BSUIR.faculties[0].courses[0].groups[0].students[2].giveMark(10, "Low speed lying on the couch");

	BSUIR.faculties[0].courses[0].groups[0].showCleverest();
	std::cout << "\n";

	BSUIR.faculties[0].courses[0].showCleverest();
	std::cout << "\n";

	BSUIR.showAllData();
	std::cout << "\n";

	BSUIR.findStudent("Wasyok number 1");
	BSUIR.findStudent("Wasyok number 25");
	std::cout << "\n";

	return 0;
}