#include "distance_rotation.h"
#include "brent.h" 
#include <math.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


//*************************************************************
// brent
//*************************************************************
// http://people.sc.fsu.edu/~jburkardt/cpp_src/brent/brent.C

float a = 0.0f;
float b = 180.0f;
float t = 0.000001f;
float eps = 10.0f*(float)sqrt((double)t);

//renvoit l'erreur minimale trouvée pour les différentes rotations testée
/*float brent (vpImage<unsigned char> *patchSrc, vpImage<unsigned char> *patchTarget, float a, float b, float eps, float t, float *x )*/
float brent (cv::Mat *ImgSrc, cv::Mat *ImgTarget, float a, float b, float eps, float t, float *x, int ax, int ay, int bx, int by, int taillePatch)
{
  float c;
  float d;
  float e;
  float fu;
  float fv;
  float fw;
  float fx;
  float m;
  float p;
  float q;
  float r;
  float sa;
  float sb;
  float t2;
  float tol;
  float u;
  float v;
  float w;
//
//  C is the square of the inverse of the golden ratio.
//
  c = 0.5f * ( 3.0f - (float)sqrt ( (double)5.0 ) );

  sa = a;
  sb = b;
  *x = sa + c * ( b - a );

  w = *x;
  v = w;
  e = 0.0;
 
  //============================
	//=====================================
  //c'est à dire MSE avec l'angle theta qui est ici la variable *x
	double sq = sqrt(2);	
	int taille2 = sq*taillePatch  ;


	cv::Mat patchSrc = sub_milieu(*ImgSrc, ax+taillePatch/2+1 ,ay+taillePatch/2+1 ,taille2);
	
	/*
	cv::namedWindow( "a envoyer", CV_WINDOW_AUTOSIZE );// Create a window for display.
   cv::imshow( "a envoyer", patchSrc  );      */

	cv::Mat patchTarget;
	patchTarget = sub(*ImgTarget, bx, by,taillePatch);

 	fx = distance_rotation(&patchSrc, &patchTarget, x, ax, ay, bx, by); //*x =angle de rotation
  //=================================================================

    
  fw = fx;
  fv = fw;

  for (int iter=1; iter<=100; iter++)                         // main loop
  {
    m = 0.5f * ( sa + sb ) ;
    tol = eps * (float)fabs ( (double)(*x) ) + t;
    t2 = 2.0f * tol;
//
//  Check the stopping criterion.
//
    if ( (float)fabs ( (float)(*x - m) ) <= t2 - 0.5 * ( sb - sa ) )
    {
      break;
    }
//
//  Fit a parabola.
//
    r = 0.0;
    q = r;
    p = q;

    if ( tol < (float)fabs ( (double)e ) )
    {
      r = ( *x - w ) * ( fx - fv );
      q = ( *x - v ) * ( fx - fw );
      p = ( *x - v ) * q - ( *x - w ) * r;
      q = 2.0f * ( q - r );
      if ( 0.0 < q )
      {
        p = - p;
      }
      q = (float)fabs ( (double)q );
      r = e;
      e = d;
    }

    if ( (float)fabs ( (double) p ) < (float)fabs ( (double) (0.5 * q * r) ) &&
         q * ( sa - *x ) < p &&   p < q * ( sb - *x ) )
    {
//
//  Take the parabolic interpolation step.
//
      d = p / q;
      u = *x + d;
//
//  F must not be evaluated too close to A or B.
//
      if ( ( u - sa ) < t2 || ( sb - u ) < t2 )
      {
        if ( *x < m )
        {
          d = tol;
        }
        else
        {
          d = - tol;
        }
      }
    }
//
//  A golden-section step.
//
    else
    {
      if ( *x < m )
      {
        e = sb - *x;
      }
      else
      {
        e = a - *x;
      }
      d = c * e;
    }
//
//  F must not be evaluated too close to X.
//
    if ( tol <= (float)fabs ( (double)d ) )
    {
      u = *x + d;
    }
    else if ( 0.0 < d )
    {
      u = *x + tol;
    }
    else
    {
      u = *x - tol;
    }

     //=================================================================
     // METTRE CODE ICI
     //c'est à dire MSE avec l'angle theta qui est ici la variable u

		cv::Mat patchSrc2 = sub_milieu(*ImgSrc, ax+taillePatch/2+1 ,ay+taillePatch/2+1 ,taille2);
	
		/*
		cv::namedWindow( "a envoyer", CV_WINDOW_AUTOSIZE );// Create a window for display.
		cv::imshow( "a envoyer", patchSrc  );      */

		cv::Mat patchTarget2;
		patchTarget2 = sub(*ImgTarget, bx, by,taillePatch);

	 	fu = distance_rotation(&patchSrc2, &patchTarget2, &u, ax, ay, bx, by); //*x =angle de rotation
     //=================================================================
//
//  Update A, B, V, W, and X.
//
    if ( fu <= fx )
    {
      if ( u < *x )
      {
        sb = *x;
      }
      else
      {
        sa = *x;
      }
      v = w;
      fv = fw;
      w = *x;
      fw = fx;
      *x = u;
      fx = fu;
    }
    else
    {
      if ( u < *x )
      {
        sa = u;
      }
      else
      {
        sb = u;
      }

      if ( fu <= fw || w == *x )
      {
        v = w;
        fv = fw;
        w = u;
        fw = fu;
      }
      else if ( fu <= fv || v == *x || v== w )
      {
        v = u;
        fv = fu;
      }
    }
  }
  return (1000.0f*fx);
}

     
