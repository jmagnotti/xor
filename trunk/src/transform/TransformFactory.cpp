#include "TransformFactory.h"


namespace XOR {

/* 
 * Return the created transform
 */
Transform * TransformFactory::CreateTransform(string data[5])
{
	Transform * transform = NULL;

	if (data[0] == "ROTATE" )
	{
		transform = Rotate::CreateRotate(atof(data[1].c_str()), atoi(data[2].c_str()),
			atoi(data[3].c_str()), atoi(data[4].c_str()) );
	}
	else if(data[0] == "TRANSLATE" )
	{
		transform = Translate::CreateTranslate(atof(data[1].c_str()), atof(data[2].c_str()),
			atof(data[3].c_str()));
	}

	return transform;
}

/*
 * Return the created transform
 */
//Transform * TransformFactory::CreateTransform(String type, String arg0, String arg1, String arg2, String arg3)
//{
//	String [5] data;
//
//	data[0] = type;
//	data[1] = arg0;
//	data[2] = arg1;
//	data[3] = arg2;
//	data[4] = arg3;
//
//	return CreateTransform(data);
//}
//

}

