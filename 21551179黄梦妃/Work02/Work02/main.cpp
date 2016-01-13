//
//  main.cpp
//  Work02
//
//  Created by 黄梦妃 on 16/1/5.
//  Copyright © 2016年 黄梦妃. All rights reserved.
//

#include <GLUT/GLUT.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include <SDL2/SDL.h>


int day = 0;

SDL_Surface* surface;

GLuint uSunTexture;
GLuint uEarthTexture;
GLuint uMoonTexture;

GLUquadricObj* qSunTexture;
GLUquadricObj* qEarthTexture;
GLUquadricObj* qMoonTexture;

SDL_Surface* pSunTexture = nullptr;
SDL_Surface* pEarthTexture = nullptr;
SDL_Surface* pMoonTexture = nullptr;

void ChangeSize(int width,int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, width / height, 1.0, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 5, 5, 0, 0, 0, 0, 1, 0);
}

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    
    glPushName(0);
    //设置太阳光照
    GLfloat light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat light_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);//光源的位置
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);//环境光强
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);//漫反射光强
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);//镜面反射光
    
    //定义太阳的材质并绘制太阳
    GLfloat sun_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat sun_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat sun_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat sun_emission[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat sun_shininess = 30.0f;
    glMaterialfv(GL_FRONT, GL_AMBIENT, sun_ambient); //材质的环境颜色
    glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_diffuse); //材质的散射颜色
    glMaterialfv(GL_FRONT, GL_SPECULAR, sun_specular); //材质的镜面反射颜色
    glMaterialfv(GL_FRONT, GL_EMISSION, sun_emission); //镜面反射指数
    glMaterialf(GL_FRONT, GL_SHININESS, sun_shininess);
    
    glBindTexture(GL_TEXTURE_2D, uSunTexture);
    glRotatef((GLfloat)day, 0, 1, 0);//设置旋转
    gluSphere(qSunTexture, 1, 30, 30);//设置球体半径和分割
    
    //定义地球材质并绘制地球
    GLfloat earth_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat earth_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };
    GLfloat earth_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat earth_emission[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat earth_shininess = 30.0f;
    glMaterialfv(GL_FRONT, GL_AMBIENT, earth_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, earth_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, earth_emission);
    glMaterialf(GL_FRONT, GL_SHININESS, earth_shininess);
    
    glBindTexture(GL_TEXTURE_2D, uEarthTexture);
    glTranslated(2.0, 0, 0);
    glRotatef((GLfloat)day*6, 0, 1, 0);
    gluSphere(qSunTexture,0.3, 20, 20);
    
    
    //定义月球材质并绘制月球
    GLfloat moon_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat moon_diffuse[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat moon_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat moon_emission[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat moon_shininess = 30.0f;
    glMaterialfv(GL_FRONT, GL_AMBIENT, moon_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, moon_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, moon_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, moon_emission);
    glMaterialf(GL_FRONT, GL_SHININESS, moon_shininess);
    
    glBindTexture(GL_TEXTURE_2D, uMoonTexture);
    glTranslated(0.6, 0, 0);
    gluSphere(qMoonTexture,0.15, 15, 15);
    glPopMatrix();
    
    glutSwapBuffers();
    glFlush();
}

void update(int id)
{
    day++;
    if (day>365)
    {
        day=0;
    }
    glutTimerFunc(30, update, 0);
    glutPostRedisplay();
}

void init()
{
    //纹理贴图
    qSunTexture = gluNewQuadric();
    gluQuadricNormals(qSunTexture, GL_SMOOTH);
    gluQuadricTexture(qSunTexture, GL_TRUE);
    
    qEarthTexture = gluNewQuadric();
    gluQuadricNormals(qEarthTexture, GL_SMOOTH);
    gluQuadricTexture(qEarthTexture, GL_TRUE);
    
    qMoonTexture = gluNewQuadric();
    gluQuadricNormals(qMoonTexture, GL_SMOOTH);
    gluQuadricTexture(qMoonTexture, GL_TRUE);
    
    //纹理坐标自动生成
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    
    pSunTexture = SDL_LoadBMP("/Users/huangmengfei/Documents/作业/opengl/opengl2015/21551179黄梦妃/Work02/Sun.bmp");
    glGenTextures(1, &uSunTexture);
    glBindTexture(GL_TEXTURE_2D, uSunTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, pSunTexture->w, pSunTexture->h, 0, GL_BGR, GL_UNSIGNED_BYTE, pSunTexture->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    pEarthTexture = SDL_LoadBMP("/Users/huangmengfei/Documents/作业/opengl/opengl2015/21551179黄梦妃/Work02/Earth.bmp");
    glGenTextures(1, &uEarthTexture);
    glBindTexture(GL_TEXTURE_2D, uEarthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, pEarthTexture->w, pEarthTexture->h, 0, GL_BGR, GL_UNSIGNED_BYTE, pEarthTexture->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    pMoonTexture = SDL_LoadBMP("/Users/huangmengfei/Documents/作业/opengl/opengl2015/21551179黄梦妃/Work02/Moon.bmp");
    glGenTextures(1, &uMoonTexture);
    glBindTexture(GL_TEXTURE_2D, uMoonTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, pMoonTexture->w, pMoonTexture->h, 0, GL_BGR, GL_UNSIGNED_BYTE, pMoonTexture->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("earth,sun,moon");
    glutReshapeFunc(ChangeSize);
    init();
    glutDisplayFunc(RenderScene);
    glutTimerFunc(30, update, 1);
    glutMainLoop();
    return 0;
}







