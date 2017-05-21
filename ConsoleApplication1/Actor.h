#pragma once


typedef struct _Bone
{
	Actor actor;
	int id;
	Bone parent;
	float ox, oy, oz;
	float px, py, pz;
	float qx, qy, qz, qw;
	float lenght;
}Bone;

typedef struct _Actor
{
	int id;
	Bone *bones;
}Actor;