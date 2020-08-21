/*
Project6 completed by Anne Glickenhaus on 02/15/2020 for CIS 410 at UofO.
All code for this project was completed by myself, and whiteboard logic was worked on
with Alyssa Kelley. Use of this program requires VTK and use of CMake.
Code worked on is in IsosurfaceTet(). All other code was provided by Hank Childs. 
Output image was compared to expected image screenshot and appeared identical to the naked eye.
*/
/*=========================================================================

  Program:   Visualization Toolkit
  Module:    SpecularSpheres.cxx

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
//
// This examples demonstrates the effect of specular lighting.
//
#include "vtkSmartPointer.h"
#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkInteractorStyle.h"
#include "vtkObjectFactory.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkProperty.h"
#include "vtkCamera.h"
#include "vtkLight.h"
#include "vtkOpenGLPolyDataMapper.h"
#include "vtkJPEGReader.h"
#include "vtkImageData.h"
#include <vtkPNGWriter.h>

#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkPolyDataReader.h>
#include <vtkCleanPolyData.h>
#include <vtkPolyDataNormals.h>
#include <vtkPoints.h>
#include <vtkUnsignedCharArray.h>
#include <vtkFloatArray.h>
#include <vtkDoubleArray.h>
#include <vtkCellArray.h>
#include <vtkDataSetReader.h>
#include <vtkContourFilter.h>
#include <vtkRectilinearGrid.h>
#include <vtkDataSetWriter.h>
#include <vtkRectilinearGridToTetrahedra.h>
#include <vtkUnstructuredGrid.h>

#include <vtkCamera.h>
#include <vtkDataSetMapper.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>


// ****************************************************************************
//  Function: GetNumberOfPoints
//
//  Arguments:
//     dims: an array of size 3 with the number of points in X, Y, and Z.
//           2D data sets would have Z=1
//
//  Returns:  the number of points in a rectilinear mesh
//
// ****************************************************************************

int GetNumberOfPoints(const int *dims)
{
    // 3D
    return dims[0]*dims[1]*dims[2];
    // 2D
    //return dims[0]*dims[1];
}

// ****************************************************************************
//  Function: GetNumberOfCells
//
//  Arguments:
//
//      dims: an array of size 3 with the number of points in X, Y, and Z.
//            2D data sets would have Z=1
//
//  Returns:  the number of cells in a rectilinear mesh
//
// ****************************************************************************

int GetNumberOfCells(const int *dims)
{
    // 3D
    return (dims[0]-1)*(dims[1]-1)*(dims[2]-1);
    // 2D
    //return (dims[0]-1)*(dims[1]-1);
}


// ****************************************************************************
//  Function: GetPointIndex
//
//  Arguments:
//      idx:  the logical index of a point.
//              0 <= idx[0] < dims[0]
//              1 <= idx[1] < dims[1]
//              2 <= idx[2] < dims[2] (or always 0 if 2D)
//      dims: an array of size 3 with the number of points in X, Y, and Z.
//            2D data sets would have Z=1
//
//  Returns:  the point index
//
// ****************************************************************************

int GetPointIndex(const int *idx, const int *dims)
{
    // 3D
    return idx[2]*dims[0]*dims[1]+idx[1]*dims[0]+idx[0];
    // 2D
    //return idx[1]*dims[0]+idx[0];
}


// ****************************************************************************
//  Function: GetCellIndex
//
//  Arguments:
//      idx:  the logical index of a cell.
//              0 <= idx[0] < dims[0]-1
//              1 <= idx[1] < dims[1]-1 
//              2 <= idx[2] < dims[2]-1 (or always 0 if 2D)
//      dims: an array of size 3 with the number of points in X, Y, and Z.
//            2D data sets would have Z=1
//
//  Returns:  the cell index
//
// ****************************************************************************

int GetCellIndex(const int *idx, const int *dims)
{
    // 3D
    return idx[2]*(dims[0]-1)*(dims[1]-1)+idx[1]*(dims[0]-1)+idx[0];
    // 2D
    //return idx[1]*(dims[0]-1)+idx[0];
}

// ****************************************************************************
//  Function: GetLogicalPointIndex
//
//  Arguments:
//      idx (output):  the logical index of the point.
//              0 <= idx[0] < dims[0]
//              1 <= idx[1] < dims[1] 
//              2 <= idx[2] < dims[2] (or always 0 if 2D)
//      pointId:  a number between 0 and (GetNumberOfPoints(dims)-1).
//      dims: an array of size 3 with the number of points in X, Y, and Z.
//            2D data sets would have Z=1
//
//  Returns:  None (argument idx is output)
//
// ****************************************************************************

void GetLogicalPointIndex(int *idx, int pointId, const int *dims)
{
    // 3D
     idx[0] = pointId%dims[0];
     idx[1] = (pointId/dims[0])%dims[1];
     idx[2] = pointId/(dims[0]*dims[1]);

    // 2D
    // idx[0] = pointId%dims[0];
    // idx[1] = pointId/dims[0];
}


// ****************************************************************************
//  Function: GetLogicalCellIndex
//
//  Arguments:
//      idx (output):  the logical index of the cell index.
//              0 <= idx[0] < dims[0]-1
//              1 <= idx[1] < dims[1]-1 
//              2 <= idx[2] < dims[2]-1 (or always 0 if 2D)
//      cellId:  a number between 0 and (GetNumberOfCells(dims)-1).
//      dims: an array of size 3 with the number of points in X, Y, and Z.
//            2D data sets would have Z=1
//
//  Returns:  None (argument idx is output)
//
// ****************************************************************************

void GetLogicalCellIndex(int *idx, int cellId, const int *dims)
{
    // 3D
    idx[0] = cellId%(dims[0]-1);
    idx[1] = (cellId/(dims[0]-1))%(dims[1]-1);
    idx[2] = cellId/((dims[0]-1)*(dims[1]-1));

    // 2D
    //idx[0] = cellId%(dims[0]-1);
    //idx[1] = cellId/(dims[0]-1);
}


class TriangleList
{
   public:
                   TriangleList() { maxTriangles = 1000000; triangleIdx = 0; pts = new float[9*maxTriangles]; };
     virtual      ~TriangleList() { delete [] pts; };

     void          AddTriangle(float X1, float Y1, float Z1, float X2, float Y2, float Z2, float X3, float Y3, float Z3);
     vtkPolyData  *MakePolyData(void);

   protected:
     float        *pts;
     int           maxTriangles;
     int           triangleIdx;
};

void
TriangleList::AddTriangle(float X1, float Y1, float Z1, float X2, float Y2, float Z2, float X3, float Y3, float Z3)
{
    pts[9*triangleIdx+0] = X1;
    pts[9*triangleIdx+1] = Y1;
    pts[9*triangleIdx+2] = Z1;
    pts[9*triangleIdx+3] = X2;
    pts[9*triangleIdx+4] = Y2;
    pts[9*triangleIdx+5] = Z2;
    pts[9*triangleIdx+6] = X3;
    pts[9*triangleIdx+7] = Y3;
    pts[9*triangleIdx+8] = Z3;
    triangleIdx++;
}

vtkPolyData *
TriangleList::MakePolyData(void)
{
    int ntriangles = triangleIdx;
    int numPoints = 3*(ntriangles);
    vtkPoints *vtk_pts = vtkPoints::New();
    vtk_pts->SetNumberOfPoints(numPoints);
    int ptIdx = 0;
    vtkCellArray *tris = vtkCellArray::New();
    tris->EstimateSize(numPoints,4);
    for (int i = 0 ; i < ntriangles ; i++)
    {
        double pt[3];
        pt[0] = pts[9*i];
        pt[1] = pts[9*i+1];
        pt[2] = pts[9*i+2];
        vtk_pts->SetPoint(ptIdx, pt);
        pt[0] = pts[9*i+3];
        pt[1] = pts[9*i+4];
        pt[2] = pts[9*i+5];
        vtk_pts->SetPoint(ptIdx+1, pt);
        pt[0] = pts[9*i+6];
        pt[1] = pts[9*i+7];
        pt[2] = pts[9*i+8];
        vtk_pts->SetPoint(ptIdx+2, pt);
        vtkIdType ids[3] = { ptIdx, ptIdx+1, ptIdx+2 };
        tris->InsertNextCell(3, ids);
        ptIdx += 3;
    }

    vtkPolyData *pd = vtkPolyData::New();
    pd->SetPoints(vtk_pts);
    pd->SetPolys(tris);
    tris->Delete();
    vtk_pts->Delete();

    return pd;
}

class Tetrahedron
{
  public:
    float X[4];
    float Y[4];
    float Z[4];
    float F[4];
    void PrintSelf()
    {
        for (int i = 0 ; i < 4 ; i++)
            printf("\tV%d: (%f, %f, %f) = %f\n", i, X[i], Y[i], Z[i], F[i]);
    };
};

void IsosurfaceTet(Tetrahedron &tet, TriangleList &tl, float isoval)
{	int numSegments[16] = {0,3,3,5,3,5,5,3,3,5,5,3,5,3,3,0}; // 3 5 6 9 10 12
	int lup[16][6]; 
	lup[0][0] = lup[0][1] = lup[0][2] = lup[0][3] = lup[0][4] = lup[0][5] = -1;
	lup[1][0] = 1; lup[1][1] = 3; lup[1][2] = 4; lup[1][3] = lup[1][4] = lup[1][5] = -1;
	lup[2][0] = 1; lup[2][1] = 2; lup[2][2] = 5; lup[2][3] = lup[2][4] = lup[2][5] = -1;
	
	lup[3][0] = 2; lup[3][1] = 3; lup[3][2] = 5; lup[3][3] = 3; lup[3][4] = 4; lup[3][5] = 5;
	
	lup[4][0] = 2; lup[4][1] = 3; lup[4][2] = 6; lup[4][3] = lup[4][4] = lup[4][5] = -1;
	
	lup[5][0] = 1; lup[5][1] = 2; lup[5][2] = 6; lup[5][3] = 1; lup[5][4] = 4; lup[5][5] = 6;
	//lup[5][0] = 1; lup[5][1] = 2; lup[5][2] = 4; lup[5][3] = 2; lup[5][4] = 4; lup[5][5] = 6;
	lup[6][0] = 1; lup[6][1] = 3; lup[6][2] = 5; lup[6][3] = 3; lup[6][4] = 5; lup[6][5] = 6;
	
	lup[7][0] = 4; lup[7][1] = 5; lup[7][2] = 6; lup[7][3] = lup[7][4] = lup[7][5] = -1;
	lup[8][0] = 4; lup[8][1] = 5; lup[8][2] = 6; lup[8][3] = lup[8][4] = lup[8][5] = -1;
	
	lup[9][0] = 1; lup[9][1] = 3; lup[9][2] = 5; lup[9][3] = 3; lup[9][4] = 5; lup[9][5] = 6;
	lup[10][0] = 1; lup[10][1] = 2; lup[10][2] = 4; lup[10][3] = 2; lup[10][4] = 4; lup[10][5] = 6;
	//lup[10][0] = 1; lup[10][1] = 2; lup[10][2] = 6; lup[10][3] = 1; lup[10][4] = 4; lup[10][5] = 6;
	
	lup[11][0] = 2; lup[11][1] = 3; lup[11][2] = 6; lup[11][3] = lup[11][4] = lup[11][5] = -1;
	
	lup[12][0] = 2; lup[12][1] = 3; lup[12][2] = 5; lup[12][3] = 3; lup[12][4] = 4; lup[12][5] = 5;
	
	lup[13][0] = 1; lup[13][1] = 2; lup[13][2] = 5; lup[13][3] = lup[13][4] = lup[13][5] = -1;
	lup[14][0] = 1; lup[14][1] = 3; lup[14][2] = 4; lup[14][3] = lup[14][4] = lup[14][5] = -1;
	lup[15][0] = lup[15][1] = lup[15][2] = lup[15][3] = lup[15][4] = lup[15][5] = -1;
	
	// int id0[3];
	// int id1[3];
	// int id2[3];
	// int id3[3];
	
	float x0, y0, z0, x1, y1, z1, x2, y2, z2, x3, y3, z3;
	
	float sclarF0;
	float sclarF1;
	float sclarF2;
	float sclarF3;
	
	int nsegments, edge1, edge2, edge3, edge4, edge5, edge6;
	float pt1[3], pt2[3], pt3[3];
	
	int icase, bin0, bin1, bin2, bin3;
	
	x0 = tet.X[0];
	x1 = tet.X[1];
	x2 = tet.X[2];
	x3 = tet.X[3];
	
	y0 = tet.Y[0];
	y1 = tet.Y[1];
	y2 = tet.Y[2];
	y3 = tet.Y[3];
	
	z0 = tet.Z[0];
	z1 = tet.Z[1];
	z2 = tet.Z[2];
	z3 = tet.Z[3];
	
	sclarF0 = tet.F[0];
	sclarF1 = tet.F[1];
	sclarF2 = tet.F[2];
	sclarF3 = tet.F[3];
	
	//printf("scalarF0 %f F1 %f F2 %f F3 %f \n", sclarF0,sclarF1,sclarF2,sclarF3);
	
	// if the scalar val is less than isoval then binary bit = 0
	
	if(sclarF0 < isoval){
		bin0 = 0;
	}
	else{
		bin0 = 1;
	}
	if(sclarF1 < isoval){
		bin1 = 0;
	}
	else{
		bin1 = 1;
	}
	if(sclarF2 < isoval){
		bin2 = 0;
	}
	else{
		bin2 = 1;
	}
	if(sclarF3 < isoval){
		bin3 = 0;
	}
	else{
		bin3 = 1;
	}
	
	icase = bin0*pow(2,0) + bin1*pow(2,1) + bin2*pow(2,2) + bin3*pow(2,3);
	
	nsegments = numSegments[icase];
	
	int numtri;
	
	if(nsegments == 5){
		numtri = 2;
	}
	else if(nsegments == 3){
		numtri = 1;
	}
	else{
		numtri = 0;
	}
	
	for(int i = 0; i< numtri; i++){
		float t;
		
		if(i == 0){
			edge1 = lup[icase][2*i];
			edge2 = lup[icase][2*i+1];
			edge3 = lup[icase][2*i+2];
		}
		else if(i == 1){
			edge1 = lup[icase][3*i];
			edge2 = lup[icase][3*i+1];
			edge3 = lup[icase][3*i+2];
		}
		
		
		if(edge1 == 1){
			t = (isoval - sclarF0)/(sclarF1-sclarF0);
			pt1[0] = x0 +  t * (x1-x0);
			pt1[1] = y0 +  t * (y1-y0);
			pt1[2] = z0 +  t * (z1-z0);
			
		}
		else if(edge1 == 2){
			t = (isoval - sclarF1)/(sclarF2-sclarF1);
			pt1[0] = x1 +  t * (x2-x1);
			pt1[1] = y1 +  t * (y2-y1);
			pt1[2] = z1 +  t * (z2-z1);
			
		}
		else if(edge1 == 3){
			t = (isoval - sclarF0)/(sclarF2-sclarF0);
			pt1[0] = x0 +  t * (x2-x0);
			pt1[1] = y0 +  t * (y2-y0);
			pt1[2] = z0 +  t * (z2-z0);
			
		}
		else if(edge1 == 4){
			t = (isoval - sclarF0)/(sclarF3-sclarF0);
			pt1[0] = x0 +  t * (x3-x0);
			pt1[1] = y0 +  t * (y3-y0);
			pt1[2] = z0 +  t * (z3-z0);
			
		}
		else if(edge1 == 5){
			t = (isoval - sclarF1)/(sclarF3-sclarF1);
			pt1[0] = x1 +  t * (x3-x1);
			pt1[1] = y1 +  t * (y3-y1);
			pt1[2] = z1 +  t * (z3-z1);
			
		}
		else if(edge1 == 6){
			t = (isoval - sclarF2)/(sclarF3-sclarF2);
			pt1[0] = x2 +  t * (x3-x2);
			pt1[1] = y2 +  t * (y3-y2);
			pt1[2] = z2 +  t * (z3-z2);
			
		}
		
		
		if(edge2 == 1){
			t = (isoval - sclarF0)/(sclarF1-sclarF0);
			pt2[0] = x0 +  t * (x1-x0);
			pt2[1] = y0 +  t * (y1-y0);
			pt2[2] = z0 +  t * (z1-z0);
			
		}
		else if(edge2 == 2){
			t = (isoval - sclarF1)/(sclarF2-sclarF1);
			pt2[0] = x1 +  t * (x2-x1);
			pt2[1] = y1 +  t * (y2-y1);
			pt2[2] = z1 +  t * (z2-z1);
			
		}
		else if(edge2 == 3){
			t = (isoval - sclarF0)/(sclarF2-sclarF0);
			pt2[0] = x0 +  t * (x2-x0);
			pt2[1] = y0 +  t * (y2-y0);
			pt2[2] = z0 +  t * (z2-z0);
			
		}
		else if(edge2 == 4){
			t = (isoval - sclarF0)/(sclarF3-sclarF0);
			pt2[0] = x0 +  t * (x3-x0);
			pt2[1] = y0 +  t * (y3-y0);
			pt2[2] = z0 +  t * (z3-z0);
			
		}
		else if(edge2 == 5){
			t = (isoval - sclarF1)/(sclarF3-sclarF1);
			pt2[0] = x1 +  t * (x3-x1);
			pt2[1] = y1 +  t * (y3-y1);
			pt2[2] = z1 +  t * (z3-z1);
			
		}
		else if(edge2 == 6){
			t = (isoval - sclarF2)/(sclarF3-sclarF2);
			pt2[0] = x2 +  t * (x3-x2);
			pt2[1] = y2 +  t * (y3-y2);
			pt2[2] = z2 +  t * (z3-z2);
			
		}
		
		if(edge3 == 1){
			t = (isoval - sclarF0)/(sclarF1-sclarF0);
			pt3[0] = x0 +  t * (x1-x0);
			pt3[1] = y0 +  t * (y1-y0);
			pt3[2] = z0 +  t * (z1-z0);
			
		}
		else if(edge3 == 2){
			t = (isoval - sclarF1)/(sclarF2-sclarF1);
			pt3[0] = x1 +  t * (x2-x1);
			pt3[1] = y1 +  t * (y2-y1);
			pt3[2] = z1 +  t * (z2-z1);
			
		}
		else if(edge3 == 3){
			t = (isoval - sclarF0)/(sclarF2-sclarF0);
			pt3[0] = x0 +  t * (x2-x0);
			pt3[1] = y0 +  t * (y2-y0);
			pt3[2] = z0 +  t * (z2-z0);
			
		}
		else if(edge3 == 4){
			t = (isoval - sclarF0)/(sclarF3-sclarF0);
			pt3[0] = x0 +  t * (x3-x0);
			pt3[1] = y0 +  t * (y3-y0);
			pt3[2] = z0 +  t * (z3-z0);
			
		}
		else if(edge3 == 5){
			t = (isoval - sclarF1)/(sclarF3-sclarF1);
			pt3[0] = x1 +  t * (x3-x1);
			pt3[1] = y1 +  t * (y3-y1);
			pt3[2] = z1 +  t * (z3-z1);
			
		}
		else if(edge3 == 6){
			t = (isoval - sclarF2)/(sclarF3-sclarF2);
			pt3[0] = x2 +  t * (x3-x2);
			pt3[1] = y2 +  t * (y3-y2);
			pt3[2] = z2 +  t * (z3-z2);
			
		}
		
		tl.AddTriangle(pt1[0], pt1[1], pt1[2], pt2[0], pt2[1], pt2[2], pt3[0], pt3[1], pt3[2]);
	}
}

int main()
{
    int  i, j;

/* If you want to try on one tetrahedron.
    Tetrahedron t;
    t.X[0] = 0;
    t.Y[0] = 0;
    t.Z[0] = 0;
    t.F[0] = 0.6;
    t.X[1] = 1;
    t.Y[1] = 0;
    t.Z[1] = 0;
    t.F[1] = 0;
    t.X[2] = 0;
    t.Y[2] = 1;
    t.Z[2] = 0;
    t.F[2] = 0;
    t.X[3] = 0.5;
    t.Y[3] = 0.5;
    t.Z[3] = 1.0;
    t.F[3] = 1;
    TriangleList tl;
    IsosurfaceTet(t, tl, 0.5);
*/

    vtkDataSetReader *rdr = vtkDataSetReader::New();
    rdr->SetFileName("proj6.vtk");
    rdr->Update();
    if (rdr->GetOutput() == NULL || rdr->GetOutput()->GetNumberOfCells() == 0)
    {
        cerr << "Could not find input file." << endl;
        exit(EXIT_FAILURE);
    }

    vtkUnstructuredGrid *ugrid = (vtkUnstructuredGrid *) rdr->GetOutput();
    float *pts = (float *) ugrid->GetPoints()->GetVoidPointer(0);
    float *F = (float *) ugrid->GetPointData()->GetScalars()->GetVoidPointer(0);
    vtkCellArray *cell_array = ugrid->GetCells();

    TriangleList tl;
    cell_array->InitTraversal();
    int ncells = cell_array->GetNumberOfCells();
    cerr << "Number of cells to tetrahedralize is " << ncells << endl;
    int cnt = 0;
    float isoval = 12.2;
    for (int i = 0 ; i < ncells ; i++)
    {
        vtkIdType npts;
        vtkIdType *ids;
        cell_array->GetNextCell(npts, ids);
        if (npts == 4)
        {
            Tetrahedron tet;
            for (int j = 0 ; j < 4 ; j++)
            {
                // This data set is in a huge bounding box.  Normalize as we go.
                tet.X[j] = (pts[3*ids[j]]+3e+7)/6e+7;
                tet.Y[j] = (pts[3*ids[j]+1]+3e+7)/6e+7;
                tet.Z[j] = (pts[3*ids[j]+2]+3e+7)/6e+7;
                tet.F[j] = F[ids[j]];
            }
            IsosurfaceTet(tet, tl, isoval);
        }
        else
        {
            cerr << "Input was non-tetrahedron!!  Ignoring..." << endl;
            cerr << "Type is " << npts << endl;
            cerr << "Cell is " << i << endl;
            cnt++;
            continue;
        }
    }

    vtkPolyData *pd = tl.MakePolyData();

/*
    //This can be useful for debugging
    vtkDataSetWriter *writer = vtkDataSetWriter::New();
    writer->SetFileName("proj6_out.vtk");
    writer->SetInputData(pd);
    writer->Write();
 */

    vtkCleanPolyData *cpd = vtkCleanPolyData::New();
    cpd->SetInputData(pd);
    cpd->SetAbsoluteTolerance(0);
    cpd->PointMergingOn();
    cpd->Update();
    vtkPolyDataNormals *pdn = vtkPolyDataNormals::New();
    pdn->SetInputData(cpd->GetOutput());
    //pdn->SetInputData(pd);
    pdn->Update();

    vtkSmartPointer<vtkDataSetMapper> win1Mapper =
      vtkSmartPointer<vtkDataSetMapper>::New();
    win1Mapper->SetInputData(pdn->GetOutput());
    win1Mapper->SetScalarRange(0, 0.15);

    vtkSmartPointer<vtkActor> win1Actor =
      vtkSmartPointer<vtkActor>::New();
    win1Actor->SetMapper(win1Mapper);

    vtkSmartPointer<vtkRenderer> ren1 =
      vtkSmartPointer<vtkRenderer>::New();

    vtkSmartPointer<vtkRenderWindow> renWin =
      vtkSmartPointer<vtkRenderWindow>::New();
    renWin->AddRenderer(ren1);

    vtkSmartPointer<vtkRenderWindowInteractor> iren =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
    iren->SetRenderWindow(renWin);
    ren1->AddActor(win1Actor);
    ren1->SetBackground(0.0, 0.0, 0.0);
    renWin->SetSize(800, 800);

    ren1->GetActiveCamera()->SetFocalPoint(0.5, 0.5, 0.5);
    ren1->GetActiveCamera()->SetPosition(0,0,-2);
    ren1->GetActiveCamera()->SetViewUp(0,1,0);
    ren1->GetActiveCamera()->SetClippingRange(0.01, 4);
    //ren1->GetActiveCamera()->SetDistance(30);

    // This starts the event loop and invokes an initial render.
    //
    iren->Initialize();
    iren->Start();

    pd->Delete();
}
