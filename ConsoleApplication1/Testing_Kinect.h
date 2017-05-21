#pragma once


#ifndef TESTING_KINECT_H
#define TESTING_KINECT_H

#pragma comment(lib, "Kinect10.lib")

#include <stdio.h>
#include <Windows.h>
#include <NuiApi.h>

class TestingKinect
{
private:
	INuiSensor *pNuiSensor;
	HANDLE kinectHandel;

public:
	HRESULT init();
	HRESULT	FindKinectSensor();
	void updateKinect();
	void SkeletonFrameReady(NUI_SKELETON_FRAME *pSkeletonframe);
	void AddBone(
		const NUI_SKELETON_DATA & skeleton,
		NUI_SKELETON_POSITION_INDEX jointFrom,
		NUI_SKELETON_POSITION_INDEX jointTo);
	void DrawSkeleton(const NUI_SKELETON_DATA &skeleton);
	void shutdown();		
};

#endif