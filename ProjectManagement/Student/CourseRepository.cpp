using namespace std;
class CourseRepository {
public:
    // Add course
    virtual void addCourse(Course* course) = 0;
    // View all courses
    virtual void viewCourses() = 0;
    // Update course
    virtual void updateCourse(int id) = 0;
    // Delete course
    virtual void deleteCourse(int id) = 0;
};   