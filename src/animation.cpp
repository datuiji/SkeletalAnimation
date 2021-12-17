#include "animation.h"
#include "glm/gtx/string_cast.hpp"
#include <iostream>


Animation::Animation(const std::string& animationPath, Model* model)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(animationPath, aiProcess_Triangulate);
    assert(scene && scene->mRootNode);
    auto animation = scene->mAnimations[0];
    m_Duration = animation->mDuration;
    m_TicksPerSecond = animation->mTicksPerSecond;
    aiMatrix4x4 globalTransformation = scene->mRootNode->mTransformation;
    globalTransformation = globalTransformation.Inverse();
    std::cout << "=================Read Heirachy==============" << std::endl;
    ReadHeirarchyData(m_RootNode, scene->mRootNode);
    ReadMissingBones(animation, *model);
}

Animation::~Animation()
{
}

Bone* Animation::FindBone(const std::string& name)
{
    auto iter = std::find_if(m_Bones.begin(), m_Bones.end(),
        [&](const Bone& Bone)
        {
            return Bone.GetBoneName() == name;
        }
    );
    
    if (iter == m_Bones.end())
    {
//        std::cout << "not found: " << name << std::endl;
        return nullptr;

    }
    else
    {
//        std::cout << "found: " << name << std::endl;
        return &(*iter);
    }
}


void Animation::ReadMissingBones(const aiAnimation* animation, Model& model)
{
    int size = animation->mNumChannels;

    auto& boneInfoMap = model.GetBoneInfoMap();//getting m_BoneInfoMap from Model class
    int& boneCount = model.GetBoneCount(); //getting the m_BoneCounter from Model class
    
    //reading channels(bones engaged in an animation and their keyframes)
    for (int i = 0; i < size; i++)
    {
        auto channel = animation->mChannels[i];
        std::string boneName = channel->mNodeName.data;
//        std::cout << boneName << std::endl;
        if (boneInfoMap.find(boneName) == boneInfoMap.end())
        {
//            std::cout << boneName << std::endl;
            boneInfoMap[boneName].id = boneCount;
            boneCount++;
        }
        auto newBone = Bone (channel->mNodeName.data,
                             boneInfoMap[channel->mNodeName.data].id,
                             channel);
        
        m_Bones.push_back(newBone);
    }

    m_BoneInfoMap = boneInfoMap;
    
    std::cout << "==========print map================" << std::endl;
    for (auto x : m_BoneInfoMap)
        std::cout << x.first << std::endl;
    
    std::cout << "==========key frame================" << std::endl;
    for(auto x : m_Bones)
        std::cout << x.GetBoneName() << std::endl;
}

void Animation::ReadHeirarchyData(AssimpNodeData& dest, const aiNode* src)
{
    assert(src);

    dest.name = src->mName.data;
    dest.transformation = AssimpGLMHelpers::ConvertMatrixToGLMFormat(src->mTransformation);
    dest.childrenCount = src->mNumChildren;
    
    std::cout << dest.name << " " << dest.childrenCount << std::endl;

    for (int i = 0; i < src->mNumChildren; i++)
    {
        AssimpNodeData newData;
        ReadHeirarchyData(newData, src->mChildren[i]);
        dest.children.push_back(newData);
    }
}
