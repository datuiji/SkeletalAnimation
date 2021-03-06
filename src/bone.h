#pragma once

#include <vector>
#include <iostream>
#include <assimp/scene.h>
#include <list>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <assimp_glm_helper.h>

struct KeyPosition
{
    glm::vec3 position;
    float timeStamp;
};

struct KeyRotation
{
    glm::quat orientation;
    float timeStamp;
};

struct KeyScale
{
    glm::vec3 scale;
    float timeStamp;
};

class Bone
{
public:
    Bone(const std::string& name, int ID, const aiNodeAnim* channel);
        
    void Update(float animationTime);
    
    glm::mat4 GetLocalTransform();
    
    std::string GetBoneName() const;
    
    int GetBoneID();

    int GetPositionIndex(float animationTime);
    
    int GetRotationIndex(float animationTime);
    
    int GetScaleIndex(float animationTime);


private:

    float GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime);
    
    glm::mat4 InterpolatePosition(float animationTime);
    
    glm::mat4 InterpolateRotation(float animationTime);
    
    glm::mat4 InterpolateScaling(float animationTime);

    std::vector<KeyPosition> m_Positions;
    std::vector<KeyRotation> m_Rotations;
    std::vector<KeyScale> m_Scales;
    int m_NumPositions;
    int m_NumRotations;
    int m_NumScalings;

    std::string m_Name;
    int m_ID;
    glm::mat4 m_LocalTransform;

};
