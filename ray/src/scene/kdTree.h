#pragma once

// Note: you can put kd-tree here

#include "bbox.h"
#include "scene.h"
#include "ray.h"
#include <iostream>

template <typename Obj>
class KdTree {
    public:
        KdTree(Scene *scene);
        ~KdTree();

        KdTree buildTree();
        
        
};

class SplitNode {
    public:
        SplitNode();
        SplitNode(glm::dvec3 position, int axis, auto* left, auto* right){
            this->position = position;
            this->axis = axis;
            this->left = left;
            this->right = right;
        }

        SplitNode* left;
        SplitNode* right;
        int axis;
        glm::dvec3 position;

        bool findIntersection();
};

class LeafNode: public SplitNode {
    public:
        LeafNode(std::vector<Geometry*> objects) {
            this->objects = objects;
        }
        std::vector<Geometry*> objects;

        bool findIntersection();
};

struct SplitPlane {
    glm::dvec3 position;
    int axis;
    int leftCount;
    double leftBBoxArea;
    int rightCount;
    double rightBBoxArea;
};