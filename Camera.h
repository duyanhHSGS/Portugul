#ifndef CAMERA_H
#define CAMERA_H

class Camera {
	private:
		float x,y,z;
	public:
		Camera();
		~Camera();
		void moveCam();
		void getViewMatrix();
};

#endif // CAMERA_H