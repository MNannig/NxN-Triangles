#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tools.h"


int main(int argc, char *argv[])
{
	if(argc != 3){ 
		fprintf(stderr, "ejecutar ./prog x y\n"); 
		exit(EXIT_FAILURE);
	}
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(1366, 768, "Sample code does not display two triangles", NULL, NULL);
    glfwMakeContextCurrent(window);

    glewInit();
    int cant_tri = atoi(argv[1]);
    int cant_li = atoi(argv[2]);
    int nvertx = (cant_tri+1);
    int nverty = (cant_li+1);
    int nvert = nvertx*nverty;
    int ntri = (cant_li)*(cant_tri);
    GLfloat *vertices = (GLfloat*)malloc(sizeof(GLfloat)*nvert*2);
    GLuint *indices = (GLuint*)malloc(sizeof(GLuint)*ntri*3);

    printf("nvert = %i    ntri %i\n", nvert, ntri); fflush(stdout);

    printf(" size vert %lu \n",sizeof(GLfloat)*nvert*2);
    printf("size ind %lu\n", sizeof(GLuint)*ntri*3);

    genvertices(vertices, nvertx, nverty);
    genindices(indices, nvertx, nverty);
    for (int i = 0; i < nvert; ++i)
    {
        printf("vert[%i] = %f  %f\n", i, vertices[i*2], vertices[i*2+1]);
    }
    for (int i = 0; i < ntri; ++i)
    {
        printf("tri[%i] = %i  %i  %i\n", i, indices[i*3], indices[i*3+1], indices[i*3 + 2]);
    }


    // copiar vertices a GPU
    GLuint vertexBufferID;
    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*nvert*2, vertices, GL_STATIC_DRAW);
    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 2, GL_FLOAT, 0, 0);

    // copiar indices a GPU
    GLuint indexBufferID;
    glGenBuffers(1, &indexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*ntri*3, indices, GL_STATIC_DRAW);
 

    while (!glfwWindowShouldClose(window))
    {
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glDrawElements(GL_TRIANGLES, ntri*3, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
return 0;
}
