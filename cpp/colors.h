#include <iostream>

using namespace std;

inline void red(double s){
	cout << "\033[31m" << s << "\033[0m";
}
inline void red(const char *s){
	cout << "\033[31m" << s << "\033[0m";
}

inline void green(double s){
	cout << "\033[32m" << s << "\033[0m";
}
inline void green(const char *s){
	cout << "\033[32m" << s << "\033[0m";
}

inline void yellow(double s){
	cout << "\033[33m" << s << "\033[0m";
}
inline void yellow(const char *s){
	cout << "\033[33m" << s << "\033[0m";
}

inline void blue(double s){
	cout << "\033[34m" << s << "\033[0m";
}
inline void blue(const char * s){
	cout << "\033[34m" << s << "\033[0m";
}
