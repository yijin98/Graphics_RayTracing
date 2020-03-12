#include "kdTree.h"

auto KDTree::BuildTree(list<Geometry*> objects, double bbox, int depth, int leafSize){
    std::vector<Geometry*> objects2;
    for (Geometry * obj: objects) {
        objects2.push_back(obj);
    }
    if (object.size() <= leafSize || depth == DEPTH_LIMIT) {
        return LeafNode(objects2);
    }
    depth = depth + 1;
    SplitPlane bestPlane = findBestSplitPlane(objects, bbox);
    list<Geometry*> leftList;
    list<Geometry*> rightList;
    for (Geometry * obj: objects){
        BoundingBox bboxObj = obj.getBoundingBox();
        glm::dvec3 bmin = bboxObj.getMin();
        glm::dvec3 bmax = bboxObj.getMax();
        glm::dvec3 position = bestPlane.position;
        if(bmin[bestPlane.axis] < position[bestPlane.axis]){
            leftList.push_back(obj);
        }
        if(bmax[bestPlane.axis] > position[bestPlane.axis]){
            rightList.push_back(obj);
        }
        if(bmin[bestPlane.axis] == position[bestPlane.axis] && bmax[bestPlane.axis] > position[bestPlane.axis] && obj.getNormal() < 0){
            leftList.push_back(obj);
        } else if(bmin[bestPlane.axis] == position[bestPlane.axis] && bmax[bestPlane.axis] > position[bestPlane.axis] && obj.getNormal() >= 0){
            rightList.push_back(obj);
        }
    }
    if(rightList.isEmpty() || leftList.isEmpty()){
        return LeafNode(objects);
    } else {
        return SplitNode(bestPlane.position, bestPlane.axis, 
                BuildTree(leftList, bestPlane.leftBBoxArea, depth, leafSize), BuildTree(rightList, bestPlane.rightBBoxArea, depth, leafSize))
    }

}

SplitPlane KDTree::findBestSplitPlane(list<Geometry*> objects, double bbox){
    list<SplitPlane> candidateList;
    for (int i = 0; i <= 2; i++){
        for (Geometry * obj: objects){
            BoundingBox bboxObj = obj.getBoundingBox();
            SplitPlane p1;
            SplitPlane p2;
            glm::dvec3 pos1 = bboxObj.getMin();
            glm::dvec3 pos2 = bboxObj.getMax();
            p1.position = pos1;
            p1.axis = i;
            p2.position = pos2;
            p2.axis = i;
            candidateList.push_back(p1);
            candidateList.push_back(p2);
        }
    }
    for (SplitPlane p: candidateList){
        for (Geometry * obj: objects){
            BoundingBox bboxObj = obj.getBoundingBox();
            glm::dvec3 bmin = bboxObj.getMin();
            glm::dvec3 bmax = bboxObj.getMax();
            if (bmin[p.axis] < p.position[p.axis]) {
                p.leftCount += 1;
                p.leftBBoxArea += bboxObj.bVolume;
            } 
            if (bmax[p.axis] > p.position[p.axis]) {
                p.rightCount += 1;
                p.rightBBoxArea += bboxObj.bVolume;
            } 
        }
    }
    SplitPlane bestPlane;
    double minSAM = DBL_MAX;
    for (SplitPlane p: candidateList){
        double SAM = (p.leftCount * p.leftBBoxArea + p.rightCount * p.rightBBoxArea) / bbox;
        if (SAM < minSAM) {
            bestPlane = p;
            minSAM = SAM;
        }
    }
    return bestPlane;
}




