#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <pthread.h>
#include <math.h>

#include "/root/workspace/include-files/cvideo.h"
#include "/root/workspace/include-files/load_image.h"
#include "/root/workspace/include-files/utility.h"
#include "/root/workspace/include-files/viewer.h"
#include "/root/workspace/include-files/TCPServerSocket.h"
#include "/root/workspace/include-files/TCPClientSocket.h"
#include "/root/workspace/include-files/image_processing.h"
#include "/root/workspace/include-files/camera.h"
#include "/root/workspace/include-files/m3dvc.h"
using namespace std;

#define numOfCamera 1
bool proximityViewEnabled=false;
int gwidth=640;
int gheight=480;
//int gwidth=512;
//int gheight=512;

utility util;
TCPClientSocket client1;
cvideo encoder;
m3dvc m3dvc_encoder(gwidth,gheight);
ImageProcessing imageproc;

int globalCounter=151;

char* fileNameNameToSave=new char[100];

char *backgroudnImage_mean;

void DWTTest(Camera data)
{

	int compressedRateDWT=4;
	//	char* grayImage=data.rawCharDepthImage;

	double* dwtOrgImage=NULL;
	//	int* oneMergeFilter=NULL;
	char* sendBuffer=NULL;
	int* blockTopLeft=NULL;
	blockTopLeft=new int[(data.width*data.height)];

	//	dwtOrgImage=util.convertShort1DToDouble1D(data.rawdepthImage,data.width,data.height);
	dwtOrgImage=util.convertArrayToDouble1D(data.rawdepthImage,data.width,data.height);

	//	oneMergeFilter=m3dvc_encoder.getEncodedDWT(dwtOrgImage,data.width,data.height);
	m3dvc_encoder.M3DVC_visible_encode(dwtOrgImage);


	//	save_pgm("/home/sklee25/Desktop/image_result_dwt/venus_synthesized_orig.pgm",sendBuffer,data.width,data.height);
	//ok

	//	int* orgIntSendBuffer=encoder.getDWTBlock(oneMergeFilter,Width,Height,compressedRateDWT);

	for(int i=0;i<(int)(data.width*data.height/4);i++)
	{
		int indexY=i/(data.width/2);
		int indexX=i%(data.width/2);

		//		blockTopLeft[(Width*indexY)+indexX]=oneMergeFilter[(Width*indexY)+indexX];
		blockTopLeft[i]=m3dvc_encoder.encoded_visible_data[(data.width*indexY)+indexX];
	}

	//	sendBuffer=util.convertIntToUintChar1D(blockTopLeft,data.width*data.height);
	//	sendBuffer=util.convertArrayToChar1D(blockTopLeft,data.width*data.height);

	//	int orgArraySize=(Width*Height)/compressedRateDWT;
	//
	//	int orgArraySize=(data.width*data.height)/compressedRateDWT;
	//	save_pgm("/home/sklee25/Desktop/image_result_dwt/3dwless_synthesized_orig.pgm",sendBuffer,data.width,data.height);
	//	getchar();
	//	client1.EstablishConnection("163.152.21.249",6000);
	//	client1.SendData(sendBuffer, orgArraySize);
	delete[] sendBuffer;
	delete[] blockTopLeft;
	//	delete[] oneMergeFilter;
	delete[] dwtOrgImage;

	sendBuffer=NULL;
	blockTopLeft=NULL;
	//	oneMergeFilter=NULL;
	dwtOrgImage=NULL;

	//	free(sendBuffer);
	//	free(blockTopLeft);
	//	free(oneMergeFilter);
	//	free(dwtOrgImage);
	//	getchar();

}

void modifiedDWTOneImage(Camera data)
{

	int compressedRateDWT=4;
	//	char* grayImage=data.rawCharDepthImage;

	double* dwtOrgImage=NULL;
	//	int* oneMergeFilter=NULL;
	char* sendBuffer=NULL;
	int* blockTopLeft=NULL;
	blockTopLeft=new int[(data.width*data.height)];

	util.startTimer();
	//	dwtOrgImage=util.convertChar1DToDouble1D(data.rawgrayImage,data.width,data.height);
	dwtOrgImage=util.convertArrayToDouble1D(data.rawgrayImage,data.width,data.height);

	//	oneMergeFilter=m3dvc_encoder.getEncodedDWT(dwtOrgImage,data.width,data.height);
	m3dvc_encoder.M3DVC_visible_encode(dwtOrgImage);
	util.getElapsedTime();

	//	save_pgm("/home/sklee25/Desktop/image_result_dwt/venus_synthesized_orig.pgm",sendBuffer,data.width,data.height);

	//	int* orgIntSendBuffer=encoder.getDWTBlock(oneMergeFilter,Width,Height,compressedRateDWT);


	for(int i=0;i<(int)(data.width*data.height/4);i++)
	{
		int indexY=i/(data.width/2);
		int indexX=i%(data.width/2);

		//		blockTopLeft[(Width*indexY)+indexX]=oneMergeFilter[(Width*indexY)+indexX];
		blockTopLeft[i]=m3dvc_encoder.encoded_visible_data[(data.width*indexY)+indexX];
	}

	//	sendBuffer=util.convertIntToUintChar1D(blockTopLeft,data.width*data.height);
	sendBuffer=util.convertArrayToChar1D(blockTopLeft,data.width*data.height);

	int orgArraySize=(data.width*data.height)/compressedRateDWT;
	//	save_pgm("/home/sklee25/Desktop/image_result_dwt/3dwless_synthesized_orig.pgm",sendBuffer,data.width,data.height);
	//	getchar();
	client1.EstablishConnection("163.152.21.249",6000);
	client1.SendData(sendBuffer, orgArraySize);
	delete[] sendBuffer;
	delete[] blockTopLeft;
	delete[] dwtOrgImage;

	sendBuffer=NULL;
	blockTopLeft=NULL;
	dwtOrgImage=NULL;

	//	free(sendBuffer);
	//	free(blockTopLeft);
	//	free(oneMergeFilter);
	//	free(dwtOrgImage);
	//	getchar();
}

//void modifiedDWTTwoImages(Camera data)
//{
//
//	int compressedRateDWT=2;
//	//	char* grayImage=data.rawCharDepthImage;
//
//	double* dwtOrgImage=NULL;
//	double* dwtGrayImage=NULL;
////	int* oneMergeFilter=NULL;
//	int* oneMergeFilterGray=NULL;
//	char* sendBuffer=NULL;
//	int* blockTopLeft=NULL;
//	blockTopLeft=new int[(data.width*data.height)/compressedRateDWT];
//
//	dwtOrgImage=util.convertShort1DToDouble1D(data.rawdepthImage,data.width,data.height);
//	dwtGrayImage=util.convertChar1DToDouble1D(data.rawgrayImage,data.width,data.height);
//
//	oneMergeFilter=m3dvc_encoder.getLowFreqArrayExt(dwtOrgImage,data.width,data.height);
//	oneMergeFilterGray=m3dvc_encoder.getLowFreqArrayExt(dwtGrayImage,data.width,data.height);
//
//	//	save_pgm("/home/sklee25/Desktop/image_result_dwt/venus_synthesized_orig.pgm",sendBuffer,data.width,data.height);
//	//ok
//
//	//	int* orgIntSendBuffer=encoder.getDWTBlock(oneMergeFilter,Width,Height,compressedRateDWT);
//
//	int indexForGray=data.width*data.height/4;
//
//	for(int i=0;i<(int)(data.width*data.height/4);i++)
//	{
//		int indexY=i/(data.width/2);
//		int indexX=i%(data.width/2);
//
//		//		blockTopLeft[(Width*indexY)+indexX]=oneMergeFilter[(Width*indexY)+indexX];
//		blockTopLeft[i]=oneMergeFilter[(data.width*indexY)+indexX];
//		blockTopLeft[i+indexForGray]=oneMergeFilterGray[(data.width*indexY)+indexX];
//	}
//
//	sendBuffer=util.convertIntToUintChar1D(blockTopLeft,data.width*data.height);
//
//	//	int orgArraySize=(Width*Height)/compressedRateDWT;
//	//
//	int orgArraySize=(data.width*data.height)/2;
//	//	save_pgm("/home/sklee25/Desktop/gray_depth_test.pgm",sendBuffer,data.width/2,data.height);
//	//	getchar();
//
//
//	client1.EstablishConnection("163.152.21.249",6000);
//	client1.SendData(client1.sock, sendBuffer, orgArraySize);
//
//	delete[] sendBuffer;
//	delete[] blockTopLeft;
//	delete[] oneMergeFilter;
//	delete[] dwtOrgImage;
//	delete[] oneMergeFilterGray;
//	delete[] dwtGrayImage;
//
//	sendBuffer=NULL;
//	blockTopLeft=NULL;
//	oneMergeFilter=NULL;
//	dwtOrgImage=NULL;
//	oneMergeFilterGray=NULL;
//	dwtGrayImage=NULL;
//
//	//	free(sendBuffer);
//	//	free(blockTopLeft);
//	//	free(oneMergeFilter);
//	//	free(dwtOrgImage);
//	//	getchar();
//
//}


void modifiedDWTWithBlock(Camera data)
{

	int compressedRateDWT=4;
	//	char* grayImage=data.rawCharDepthImage;

	double* dwtOrgImage=NULL;
	char* sendBuffer=NULL;
	//	util.startTimer();

	//	dwtOrgImage=util.convertChar1DToDouble1D(data.rawgrayImage,data.width,data.height);
	dwtOrgImage=util.convertArrayToDouble1D(data.rawgrayImage,data.width,data.height);

	m3dvc_encoder.M3DVC_visible_encode(dwtOrgImage);
	//	util.getElapsedTime();


	data.getRealDepthValue();
	m3dvc_encoder.M3DVC_depth_encode_2(data.realDepthVal1D);

	m3dvc_encoder.mergeVisibleDepthData();
	//	sendBuffer=util.convertIntToUintChar1D(m3dvc_encoder.encoded_merge_visible_depth_data,(data.width*data.height)/2);
	sendBuffer=util.convertArrayToChar1D(m3dvc_encoder.encoded_merge_visible_depth_data,(data.width*data.height)/2);

	int orgArraySize=(data.width*data.height)/2;
	//	save_pgm("/home/sklee25/Desktop/image_result_dwt/3dwless_synthesized_orig.pgm",sendBuffer,data.width,data.height);
	//	getchar();
	client1.EstablishConnection("163.152.21.249",6000);
	client1.SendData(sendBuffer, orgArraySize);

	delete[] sendBuffer;
	delete[] dwtOrgImage;

	sendBuffer=NULL;
	dwtOrgImage=NULL;

}


//divide the images into 4*4 matrix
int* decodeBlock_4(short* orgArray, int width, int height)
{
	int* returnVal=new int[width*height/16];
	int depthHolder=0;
	int depthHolder1=0;
	int depthHolder2=0;
	int depthHolder3=0;

	int returnValIndex=0;
	for(int i=0;i<width*height;i=i+4)
	{
		int indexY=i/(width);
		int indexX=i%(width);
		if(indexY%4!=0)
		{
			//			indexY++;
			i=i+width-4;
		}
		else
		{
			depthHolder=(int)(orgArray[i]+orgArray[i+1]+orgArray[i+2]+orgArray[i+3])/4;
			depthHolder1=(int)(orgArray[i+width]+orgArray[i+(width+1)]+orgArray[i+(width+2)]+orgArray[i+(width+3)])/4;
			depthHolder2=(int)(orgArray[i+width*2]+orgArray[i+(width*2+1)]+orgArray[i+(width*2+2)]+orgArray[i+(width*2+3)])/4;
			depthHolder3=(int)(orgArray[i+width*3]+orgArray[i+(width*3+1)]+orgArray[i+(width*3+2)]+orgArray[i+(width*3+3)])/4;
			returnVal[returnValIndex]=(depthHolder+depthHolder1+depthHolder2+depthHolder3)/4;
			returnValIndex++;
			//						printf("%d  %d\n",indexY,indexX);
		}
	}
	//	printf("%d\n",returnValIndex);
	//	getchar();
	return returnVal;
}

void storeDispVal_block_method_4(Camera* data, int** returnVal, int* testVal)
{
	int widthIndex=0;
	int heightIndex=0;
	double valToSave=0;
	double valToSave2=0;

	int* expVal=new int[data->height*data->width];
	int expValIndex=0;
	for(int i=0;i<data->height*data->width/16;i++)
	{
		int indexY=expValIndex/(data->width);
		int indexX=expValIndex%(data->width);

		if(indexY%4!=0)
		{
			//			indexY++;
			expValIndex=data->width*3+expValIndex;
			i=i--;
		}
		else
		{
			expVal[data->width*indexY+indexX]=testVal[i];
			expVal[data->width*indexY+indexX+1]=testVal[i];
			expVal[data->width*indexY+indexX+2]=testVal[i];
			expVal[data->width*indexY+indexX+3]=testVal[i];
			expVal[data->width*(indexY+1)+indexX]=testVal[i];
			expVal[data->width*(indexY+1)+(indexX+1)]=testVal[i];
			expVal[data->width*(indexY+1)+(indexX+2)]=testVal[i];
			expVal[data->width*(indexY+1)+(indexX+3)]=testVal[i];
			expVal[data->width*(indexY+2)+(indexX)]=testVal[i];
			expVal[data->width*(indexY+2)+(indexX+1)]=testVal[i];
			expVal[data->width*(indexY+2)+(indexX+2)]=testVal[i];
			expVal[data->width*(indexY+2)+(indexX+3)]=testVal[i];
			expVal[data->width*(indexY+3)+(indexX)]=testVal[i];
			expVal[data->width*(indexY+3)+(indexX+1)]=testVal[i];
			expVal[data->width*(indexY+3)+(indexX+2)]=testVal[i];
			expVal[data->width*(indexY+3)+(indexX+3)]=testVal[i];
			expValIndex=expValIndex+4;
		}
		//		printf("%d %d\n",indexY,indexX);
	}
	int diffCount=0;
	for(int k=0;k<data->height*data->width;k++)
	{
		//						printf("%f\n",0.1236 * tan((double)data[0].rawdepthImage[i]/ 2842.5 + 1.1863));
		double raw_depth=(double)data->rawdepthImage[k];
		double raw_depth1=expVal[k];
		widthIndex=k%data->width;


		if (raw_depth < 2047)
		{
			//					fprintf(pFile,"%f,",(1.0 / (raw_depth * -0.0030711016 + 3.3309495161))*10);
			//			printf("%f,",(1.0 / (raw_depth * -0.0030711016 + 3.3309495161))*10);
			//
			//
			//			printf("--------------------%f\n",(1.0 / (raw_depth1 * -0.0030711016 + 3.3309495161))*10);
			int temp1=(int)((1.0 / (raw_depth * -0.0030711016 + 3.3309495161)))*10;
			int temp2=(int)((1.0 / (raw_depth1 * -0.0030711016 + 3.3309495161)))*10;

			if((temp1-temp2)!=0)
			{
				diffCount++;
			}

			valToSave=(1.0 / (raw_depth * -0.0030711016 + 3.3309495161))*10;
			valToSave2=(1.0 / (raw_depth1 * -0.0030711016 + 3.3309495161))*10;
			returnVal[heightIndex][widthIndex]=(int)valToSave2;
		}
		else
		{
			raw_depth=0;
			raw_depth1=0;
			int temp1=(int)((1.0 / (raw_depth * -0.0030711016 + 3.3309495161)))*10;
			int temp2=(int)((1.0 / (raw_depth1 * -0.0030711016 + 3.3309495161)))*10;

			valToSave=(1.0 / (raw_depth * -0.0030711016 + 3.3309495161))*10;
			valToSave2=(1.0 / (raw_depth * -0.0030711016 + 3.3309495161))*10;
			if((temp1-temp2)!=0)
			{
				diffCount++;
			}

			returnVal[heightIndex][widthIndex]=(int)valToSave2;
		}

		if(k%data->width==0 && k!=0)
		{
			//					fprintf(pFile,"\n");
			//			printf("\n");
			heightIndex++;
		}
	}
	printf("diff percentage is %f\n",(double)diffCount/(307200.00)*100);
	//	getchar();
}





void encodeDepthBlock_4(short* orgArray, int* returnVal, int width, int height)
{


}

IplImage* blockData(int* blockVal)
{
	//			int* blockVal=blockTest(data[0].rawdepthImage, data[0].width, data[0].height);
	//		storeDispVal_test(&data[0],intReturnVal,blockVal);

	//		//////////////////////////////////////////////////
	int* expVal=new int[gheight*gwidth];
	int expValIndex=0;
	for(int i=0;i<gheight*gwidth/16;i++)
	{
		int indexY=expValIndex/(gwidth);
		int indexX=expValIndex%(gwidth);

		if(indexY%4!=0)
		{
			//			indexY++;
			expValIndex=gwidth*3+expValIndex;
			i=i--;
		}
		else
		{
			expVal[gwidth*indexY+indexX]=blockVal[i];
			expVal[gwidth*indexY+indexX+1]=blockVal[i];
			expVal[gwidth*indexY+indexX+2]=blockVal[i];
			expVal[gwidth*indexY+indexX+3]=blockVal[i];
			expVal[gwidth*(indexY+1)+indexX]=blockVal[i];
			expVal[gwidth*(indexY+1)+(indexX+1)]=blockVal[i];
			expVal[gwidth*(indexY+1)+(indexX+2)]=blockVal[i];
			expVal[gwidth*(indexY+1)+(indexX+3)]=blockVal[i];
			expVal[gwidth*(indexY+2)+(indexX)]=blockVal[i];
			expVal[gwidth*(indexY+2)+(indexX+1)]=blockVal[i];
			expVal[gwidth*(indexY+2)+(indexX+2)]=blockVal[i];
			expVal[gwidth*(indexY+2)+(indexX+3)]=blockVal[i];
			expVal[gwidth*(indexY+3)+(indexX)]=blockVal[i];
			expVal[gwidth*(indexY+3)+(indexX+1)]=blockVal[i];
			expVal[gwidth*(indexY+3)+(indexX+2)]=blockVal[i];
			expVal[gwidth*(indexY+3)+(indexX+3)]=blockVal[i];
			expValIndex=expValIndex+4;
		}
		//				printf("%d %d\n",indexY,indexX);
	}
	char* fileName2=new char[100];
	sprintf(fileName2,"/home/sklee25/Desktop/test/test_decode_%d.pgm",globalCounter);

	IplImage* testImg=imageproc.convertGrayArrayToIplImage(expVal,gwidth,gheight);
	//			cvSaveImage(fileName2,testImg);
	//			cvShowImage("main", testImg);
	globalCounter++;
	return testImg;
	//		//////////////////////////////////////////////////
}


void modifiedDWTWithBlock_visual_quality_test(Camera data)
{

	int compressedRateDWT=4;
	//	char* grayImage=data.rawCharDepthImage;

	double* dwtOrgImage=NULL;
	char* sendBuffer=NULL;
	//	util.startTimer();

	//	dwtOrgImage=util.convertChar1DToDouble1D(data.rawgrayImage,data.width,data.height);
	dwtOrgImage=util.convertArrayToDouble1D(data.rawgrayImage,data.width,data.height);

	m3dvc_encoder.M3DVC_visible_encode(dwtOrgImage);
	//	util.getElapsedTime();
	m3dvc m3dvc_decoder(gwidth,gheight);



	for(int j=0;j<data.width*data.height;j++)
	{
		m3dvc_decoder.decoded_reduced_visible_data[j]=m3dvc_encoder.encoded_reduced_visible_data[j];
	}

	m3dvc_decoder.getReplicateBlocks(compressedRateDWT);
	m3dvc_decoder.M3DVC_visible_decode();

	char* returnArray=new char[data.width*data.height];
	for(int i=0;i<data.width*data.height;i++)
	{
		returnArray[i]=(uint8_t)m3dvc_decoder.reconstructed_visible_data[i];
	}
	sprintf (fileNameNameToSave, "/home/sklee25/Desktop/rema_result2/rema_reconstrcuted_%d.pgm", globalCounter);
//	sprintf(fileNameNameToSave,"/home/sklee25/Desktop/rema_static_image_result/1 (%d).pgm",globalCounter);


	save_pgm(fileNameNameToSave,returnArray,data.width,data.height);
	//		sprintf (fileNameNameToSave, "/home/sklee25/Desktop/image_result_dwt/%s_%d_decode_result.pgm","received",index);
	//		save_pgm(fileNameNameToSave,finalImage,data.width,data.height);

	//	sendBuffer=util.convertIntToUintChar1D(m3dvc_encoder.encoded_merge_visible_depth_data,(data.width*data.height)/2);
	cout<<"test123"<<endl;
//	getchar();


}

int main(int argc, char **argv) {
	int NumOfGrabbedImages=0;

	Camera data[numOfCamera];//=new Camera[numOfCamera];
	//	data[0].initKinect();

	for(int i=0;i<numOfCamera;i++)
	{
		data[i]=Camera(i);
	}

	if(proximityViewEnabled==true)
	{
		cvNamedWindow("main_display", CV_WINDOW_AUTOSIZE);
	}

	char* fileName=new char[100];

	//	util.initWritingFile("/home/sklee25/Desktop/test_decode/test.txt");

	while(1)
	{
		IplImage* decoded=0;

		//loading image
		for(int i=0;i<numOfCamera;i++)
		{
			data[i].height=gheight;
			data[i].width=gwidth;
			//						data[i].rawrgbImage=GrabKinectRGBImage(i);
			//						data[i].grabKinectGrayImage();
			//			data[i].grabKinectDepthImage();
			while(globalCounter<338)
			{
				sprintf(fileName,"/home/sklee25/Desktop/rema_test_set2/original_%d.pgm",globalCounter);
//				sprintf(fileName,"/home/sklee25/Desktop/rema_static_image_original/1 (%d).pgm",globalCounter);
				data[i].grayImage=cvLoadImage(fileName,-1);
				printf("load image number %d\n",globalCounter);
				imageproc.convertIplImageToCharArray(data[i].rawgrayImage,data[i].grayImage,data[i].height,data[i].width);
				modifiedDWTWithBlock_visual_quality_test(data[i]);
				printf("test\n");

				printf("image number %d\n",globalCounter);
				globalCounter++;
			}
			printf("done\n");
			getchar();


			//			for(int i=0;i<data[i].height;i++)
			//			{
			//				for(int j=0;j<data[i].width;j++)
			//				{
			//					returnArray[i*width+j]=((uchar*)(orgImage->imageData+i*orgImage->widthStep))[j];
			//				}
			//			}

			//			m3dvc_encoder.M3DVC_visible_encode(dwtOrgImage);


			//			data[i].depthImage=imageproc.convertGrayArrayToIplImage(data[i].rawdepthImage,data[i].width,data[i].height);
			//			cvSaveImage(fileName,data[i].depthImage);


			//			data[i].rgbImage=convertColorArrayToIplImage(data[i].rawrgbImage, data[i].height, data[i].width);
			//			cvSaveImage("/home/sklee25/Desktop/depth_orig.pgm",data[i].depthImage);
			//			save_pgm("/home/sklee25/Desktop/gray_orig.pgm",data[i].rawgrayImage,640,480);

			//			DWTTest(data[i]);
			//			modifiedDWTTwoImages(data[i]);
			//			modifiedDWTOneImage(data[i]);

			int* test=decodeBlock_4(data[i].rawdepthImage,data[i].width,data[i].height);
			decoded=blockData(test);
			//			modifiedDWTWithBlock(data[i]);
		}




		for(int i=0;i<decoded->height;i++)
		{
			for(int j=0;j<decoded->width;j++)
			{
				int leftImgPixel=((uchar*)(decoded->imageData+i*decoded->widthStep))[j];
				int leftImgPixelorg=((uchar*)(data[0].depthImage->imageData+i*data[0].depthImage->widthStep))[j];
				if(leftImgPixel!=leftImgPixelorg)
				{
					globalCounter++;
				}
			}
		}
		util.writeToFile(globalCounter);
		printf("%d\n",globalCounter);
		globalCounter=0;

		//For real-time intermediate view synthesis-color
		//		storeDispVal(&data[0],intReturnVal);
		//		data[0].rgbImage=convertColorArrayToIplImage(data[0].rawrgbImage,data[0].height,data[0].width);
		//		IplImage* ilImage=getSynthesizedImage(data[0].rgbImage,data[0].rgbImage,intReturnVal,0.1);

		//For real-time intermediate view synthesis-gray
		//		data[0].grayImage=convertCharGrayArrayToIplImage(data[0].rawgrayImage,data[0].height,data[0].width);
		//		data[0].intermediateImage=getSynthesizedImage_gray_ext(data[0].grayImage,data[0].grayImage,data[0].decodedBlock,0.5);
		//		cvShowImage("main", data[0].intermediateImage);
		//		cvShowImage("right", data[0].grayImage);

		//For displaying the view from the client side
		//		for(int i=0;i<numOfCamera;i++)
		//		{
		//			sprintf(rgbWindowName,"image_image%d",i);
		//			sprintf(depthWindowName,"depth_image%d",i);
		//
		//			cvShowImage(rgbWindowName, data[i].rgbImage);
		//			cvShowImage(depthWindowName, data[i].depthImage);
		//
		//		}



		//proximity view switch implementation-end
		cvWaitKey(2);
		for(int i=0;i<numOfCamera;i++)
		{
			data[i].cleanImageMemory();
		}
		//		printf("%d\n",NumOfGrabbedImages);
		NumOfGrabbedImages++;
	}

	//Works with the video callback function
	/****************************************************************************************************************************/
	//	int res;
	//
	//	depth_mid = (char*)malloc(640*480*3);
	//	depth_front = (char*)malloc(640*480*3);
	//
	//	printf("Kinect camera test\n");
	//
	//	int i;
	//	for (i=0; i<2048; i++) {
	//		float v = i/2048.0;
	//		v = powf(v, 3)* 6;
	//		t_gamma[i] = v*6*256;
	//	}
	//
	//	g_argc = argc;
	//	g_argv = argv;
	//
	//	if (freenect_init(&f_ctx, NULL) < 0) {
	//		printf("freenect_init() failed\n");
	//		return 1;
	//	}
	//
	//	freenect_set_log_level(f_ctx, FREENECT_LOG_DEBUG);
	//	freenect_select_subdevices(f_ctx, (freenect_device_flags)(FREENECT_DEVICE_MOTOR | FREENECT_DEVICE_CAMERA));
	//
	//	int nr_devices = freenect_num_devices (f_ctx);
	//	printf ("Number of devices found: %d\n", nr_devices);
	//
	//	int user_device_number = 0;
	//	if (argc > 1)
	//		user_device_number = atoi(argv[1]);
	//
	//	if (nr_devices < 1)
	//		return 1;
	//
	//	if (freenect_open_device(f_ctx, &f_dev, user_device_number) < 0) {
	//		printf("Could not open device\n");
	//		return 1;
	//	}
	//
	//	RunKinect();
	/****************************************************************************************************************************/

	//Actual part where the threads begin to grab the images
	//////////////////////////////////////////////////////////////////////
	//	res = pthread_create(&freenect_thread, NULL, freenect_threadfunc, NULL);
	//	if (res) {
	//		printf("pthread_create failed\n");
	//		return 1;
	//	}
	//
	//	// OS X requires GLUT to run on the main thread
	//	gl_threadfunc(NULL);

	for(int i=0;i<numOfCamera;i++)
	{
		data[i].~Camera();
	}
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}



