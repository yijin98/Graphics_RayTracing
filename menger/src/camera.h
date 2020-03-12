#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

class Camera {
public:
	glm::mat4 get_view_matrix() const;
  glm::mat4 lookAt() const;
  void switchMode();
  void setMouseMovement(bool event);
  bool getMouseMovement();
  void setMousePos(double mouse_x, double mouse_y);
  void rotateMouse(double mouse_x, double mouse_y);
  void roll(bool left);
  void zoomMouse(double mouse_y);
  void zoomKey(bool forward);
  void panHor(bool left);
  void panVert(bool up);
private:
	float camera_distance_ = 3.0;
	glm::vec3 Camera_look = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Camera_up = glm::vec3(0.0f, 1.0, 0.0f);
	glm::vec3 Camera_eye = glm::vec3(0.0f, 0.0f, camera_distance_);
	// Note: you may need additional member variables
  double saved_mouse_x;
  double saved_mouse_y;
  bool fps_mode = false;
  bool mouse_pressed = true; 
  glm::vec3 Camera_center = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 Camera_tangent = glm::normalize(glm::cross(Camera_look, Camera_up));
};

#endif
