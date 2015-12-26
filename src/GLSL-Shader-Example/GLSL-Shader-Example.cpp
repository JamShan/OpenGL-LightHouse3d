#include <GL/glew.h>
#include <GL/freeglut.h>
#include <ogl/shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Shader matrixShader("glsl test");
GLuint program, vertex_loc, mvp_matrix_loc;
GLuint color_loc;

static const GLfloat VertexData[] = 
{
	0.0f,  0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f
};

void init_shader()
{
	matrixShader.init();
	matrixShader.attach(GL_VERTEX_SHADER, "shader.vert");
	matrixShader.attach(GL_FRAGMENT_SHADER, "shader.frag");
	matrixShader.link();
	matrixShader.use();
	program = matrixShader.GetProgram();
	mvp_matrix_loc = glGetUniformLocation(program, "mvp_matrix");
	color_loc = glGetUniformLocation(program, "color");

}

void init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	init_shader();
}

static float ry = 0.0;

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	glUseProgram(program);
	glUniform4f(color_loc, sin(time), cos(time), 1.0, 0.0); //ע����ĸ�Ԫ����alpha��������0Ϊ͸��
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotatef(ry, 0.0, 1.0, 0.0);
	glutSolidTeapot(1.0f);
	ry += 0.1f;
	glutSwapBuffers();
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 720.0 / 640.0, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);

}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(300, 0);
	glutInitWindowSize(720, 640);
	glutCreateWindow("glsl-Shader-Example");
	GLenum status = glewInit();
	if (status != GLEW_OK)
		std::cerr << glewGetErrorString(status) << std::endl;
	init();
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}