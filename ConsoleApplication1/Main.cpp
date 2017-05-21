#include "Testing_Kinect.h"

static TestingKinect *testing;

int main(int argc, char *argv[]) {
	testing = new TestingKinect();
	
	if (testing->init() == S_OK) {
		do {
			testing->updateKinect();
			Sleep(1000);
		} while (true);
	}
	system("pause");
}