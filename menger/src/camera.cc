#include <fstream>
#include <iostream>
#include "camera.h"

namespace {
	float pan_speed = 0.1f;
	float roll_speed = 0.1f;
	float rotation_speed = 0.05f;
	float zoom_speed = 0.1f;
};

glm::mat4 Camera::get_view_matrix() const
{
  return lookAt();
}

glm::mat4 
Camera::lookAt() const{
  glm::mat4 matrix;
  glm::vec3 Z = glm::normalize(Camera_eye - Camera_center);
  glm::vec3 Y = Camera_up;
  glm::vec3 X = glm::cross(Y, Z);
  Y = glm::normalize(glm::cross(Z, X));
  X = glm::normalize(X);
  matrix[0][0] = X[0];
  matrix[1][0] = X[1];
  matrix[2][0] = X[2];
  matrix[3][0] = -glm::dot(X, Camera_eye);
  matrix[0][1] = Y[0];
  matrix[1][1] = Y[1];
  matrix[2][1] = Y[2];
  matrix[3][1] = -glm::dot(Y, Camera_eye);
  matrix[0][2] = Z[0];
  matrix[1][2] = Z[1];
  matrix[2][2] = Z[2];
  matrix[3][2] = -glm::dot(Z, Camera_eye);
  matrix[0][3] = 0;
  matrix[1][3] = 0;
  matrix[2][3] = 0;
  matrix[3][3] = 1;
  return matrix;
}

void
Camera::switchMode() {
  (fps_mode) ? fps_mode = false : fps_mode = true;
}

void
Camera::setMouseMovement(bool event) {
  mouse_pressed = event;
}

bool
Camera::getMouseMovement() {
  return mouse_pressed;
}

void
Camera::setMousePos(double mouse_x, double mouse_y) {
  saved_mouse_x = mouse_x;
  saved_mouse_y = mouse_y;
}

void 
Camera::rotateMouse(double mouse_x, double mouse_y) {
  double delta_x = mouse_x - saved_mouse_x;
  double delta_y = mouse_y - saved_mouse_y;
  setMousePos(mouse_x, mouse_y);
  if(fps_mode) {
    Camera_look = glm::rotate(Camera_look, (float)delta_x * rotation_speed, Camera_up);
    Camera_tangent = glm::normalize(glm::cross(Camera_look, Camera_up));
    Camera_look = glm::rotate(Camera_look, (float)delta_y * rotation_speed, Camera_tangent);
    Camera_up = glm::normalize(glm::cross(Camera_look, -Camera_tangent));
    Camera_center = Camera_look * camera_distance_ + Camera_eye;
  }
  else {
    Camera_eye = glm::rotate(Camera_eye, (float)delta_x * rotation_speed, Camera_up);
    Camera_look = Camera_center - Camera_eye;
    Camera_tangent = glm::normalize(glm::cross(Camera_look, Camera_up));
    Camera_eye = glm::rotate(Camera_eye, (float)delta_y * rotation_speed, Camera_tangent);
    Camera_look = Camera_center - Camera_eye;
    Camera_up = glm::normalize(glm::cross(Camera_look, -Camera_tangent));
  }
  Camera_look = glm::normalize(Camera_look);
}

void
Camera::roll(bool left) {
  if(left)
    Camera_up = glm::normalize(glm::rotate(Camera_up, -roll_speed, Camera_look));
  else
    Camera_up = glm::normalize(glm::rotate(Camera_up, roll_speed, Camera_look));
  Camera_tangent = glm::normalize(glm::cross(Camera_look, Camera_up));
}
void
Camera::zoomMouse(double mouse_y) {
  glm::vec3 scale = Camera_look * (zoom_speed * (float)(saved_mouse_y - mouse_y));
  Camera_eye += scale;
  camera_distance_ = glm::length(Camera_center - Camera_eye);
  setMousePos(0.0, mouse_y);
}

void
Camera::zoomKey(bool forward) {
  glm::vec3 scale = Camera_look * zoom_speed;
  if(fps_mode) {
    if(forward) {
      Camera_eye += scale;
      Camera_center += scale;
    }
    else {
      Camera_eye -= scale;
      Camera_center -= scale;
    }
  }
  else {
    float distance = glm::length(Camera_center - Camera_eye);
    if(forward) {
      camera_distance_ = distance - zoom_speed;
      Camera_eye += scale;
    }
    else {
      camera_distance_ = distance + zoom_speed;
      Camera_eye -= scale;
    }
  }
}

void
Camera::panHor(bool left) {
  if(left) {
    Camera_center -= Camera_tangent * pan_speed;
    Camera_eye -= Camera_tangent * pan_speed;
  }
  else {
    Camera_center += Camera_tangent * pan_speed;
    Camera_eye += Camera_tangent * pan_speed;
  }
}

void
Camera::panVert(bool up) {
  if(up) {
    Camera_center += Camera_up * pan_speed;
    Camera_eye += Camera_up * pan_speed;
  }
  else {
    Camera_center -= Camera_up * pan_speed;
    Camera_eye -= Camera_up * pan_speed;
  }
}
