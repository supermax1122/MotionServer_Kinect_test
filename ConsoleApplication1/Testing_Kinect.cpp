#include "Testing_Kinect.h"

HRESULT TestingKinect::init()
{
	
	HRESULT result;
	printf("Check kinect connection.\n");
	result = FindKinectSensor();

	if (FAILED(result)) {
		printf("Cannot find connect kinect.\n");
		return result;
	}

	printf("Initialize kinect.\n");
	result = pNuiSensor->NuiInitialize(NUI_INITIALIZE_FLAG_USES_SKELETON);

	
	if (FAILED(result)) {
		printf("Cannot open kinect.\n");
		return result;
	}

	kinectHandel = CreateEventW(NULL, TRUE, FALSE, NULL);

	printf("Enable kinect Traking.\n");
	result = pNuiSensor->NuiSkeletonTrackingEnable(kinectHandel, NUI_SKELETON_TRACKING_FLAG_ENABLE_SEATED_SUPPORT);

	if (FAILED(result)) {
		printf("Cannot enable to track skeleton.\n");
		return result;
	}

	return result;
}

HRESULT	TestingKinect::FindKinectSensor()
{
	return NuiCreateSensorByIndex(0, &pNuiSensor);
}

void TestingKinect::updateKinect()
{
	printf("update kinect state.\n");

	if (WAIT_OBJECT_0 == WaitForSingleObject(kinectHandel, 0)) {
		NUI_SKELETON_FRAME skeletonFrame = {0};

		printf("get skeleton frame.\n");
		if (SUCCEEDED(pNuiSensor->NuiSkeletonGetNextFrame(0, &skeletonFrame)))
		{
			SkeletonFrameReady(&skeletonFrame);
		}
	}
}

void TestingKinect::SkeletonFrameReady(NUI_SKELETON_FRAME *pSkeletonFrame)
{
	printf("Draw Skeleton.\n");
	for (int i = 0; i < NUI_SKELETON_COUNT; i++)
	{
		const NUI_SKELETON_DATA &skeleton = pSkeletonFrame->SkeletonData[i];

		printf("x: %d", skeleton.dwTrackingID);
		switch (skeleton.eTrackingState)
		{
		case NUI_SKELETON_TRACKED:
			DrawSkeleton(skeleton);
			break;
		case NUI_SKELETON_POSITION_ONLY:
			DrawSkeleton(skeleton);
			break;
		}
	}
}

void TestingKinect::DrawSkeleton(const NUI_SKELETON_DATA &skeleton)
{
	//sample to show the position
	const Vector4 &point = skeleton.SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT];

	printf("RIGHT Hand x: %f", point.x);
	printf("RIGHT Head y: %f", point.y);
	printf("RIGHT Head z: %f", point.z);
	printf("RIGHT Head w: %f", point.w);

}

void TestingKinect::AddBone(
	const NUI_SKELETON_DATA & skeleton,
	NUI_SKELETON_POSITION_INDEX jointFrom,
	NUI_SKELETON_POSITION_INDEX jointTo) {
}

void TestingKinect::shutdown()
{
	NuiShutdown();
}