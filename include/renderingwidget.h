#ifndef RENDERINGWIDGET_H
#define RENDERINGWIDGET_H

#define GL_GLEXT_PROTOTYPES

#include <QtOpenGL/QGLWidget>
#include <pipeline_cpu.h>
#include <pipeline_gpu.h>
#include <QColor>
#include <QRgb>
#include <configxml.h>
#include <vector>

using namespace std;

/// Gets the openGL error string (emulates gluErrorString())

inline const char* glErrorString(GLenum err)

{

    switch ( err )

    {

        case GL_INVALID_ENUM:

            return " Invalid enum : An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.\n";

        case GL_INVALID_VALUE:

            return " Invalid value : A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.\n";

        case GL_INVALID_OPERATION:

            return " Invalid operation : The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.\n";

        case GL_INVALID_FRAMEBUFFER_OPERATION:

            return " Invalid framebuffer operation : The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag.\n";

        case GL_OUT_OF_MEMORY:

            return " Out of memory : There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.\n";

        // case GL_STACK_UNDERFLOW:

        //    return " Stack underflow : An attempt has been made to perform an operation that would cause an internal stack to underflow.\n";

        //case GL_STACK_OVERFLOW:

        //    return " Stack overflow : An attempt has been made to perform an operation that would cause an internal stack to overflow.\n";

        case GL_NO_ERROR:

            return " No error\n";

        default:

            return " Unknown GL error\n";

    }

}

// FIXME(Charly): Fix logging



#define GL_ASSERT(x) \
x; { \
GLuint err = glGetError(); \
if (err != GL_NO_ERROR) { \
    const char* errBuf = glErrorString(err); \
    std::cout << "OpenGL error (" << __FILE__ << ":" << __LINE__ \
                  << ", " << STRINGIFY(x) << ") : " << errBuf << "(" \
                  << err << " : 0x" << std::hex << err << std::dec << ")."; \
} \
}

/// This macro will query the last openGL error.

#define GL_CHECK_ERROR \
{\
GLuint err = glGetError(); \
if (err != GL_NO_ERROR) { \
    const char* errBuf = glErrorString(err); \
    std::cout << "OpenGL error (" << __FILE__ << ":" << __LINE__ \
                  << ", glCheckError()) : " << errBuf << "(" \
                  << err << " : 0x" << std::hex << err << std::dec << ")."; \
} \
}



class RenderingWidget : public QGLWidget
{
    Q_OBJECT
public:
    RenderingWidget(const QGLFormat & format, QWidget * parent = 0);
    ~RenderingWidget();

    QColor getResultat();
    glm::vec3 getResultatFloatPrecision();
    vector<QString> getPigmentsLabels();

    void setLabel_pigment1(QString label);
    void setLabel_pigment2(QString label);
    void setSlider_concentration(float concentration);


    virtual void initializeGL();

protected:


    virtual void resizeGL(int w, int h);
    virtual void paintGL();

private:

    Pigment * getPigmentfromLabel(const QString& name);
    Light * getLightfromLabel(const QString& name);

    Pipeline * pipe_cpu;
    Pipeline_GPU * pipe_gpu;

    vector<Pigment> pigments;
    vector<Light> lumieres;

    float slider_concentration;
    QString label_pigment1;
    QString label_pigment2;
    QString lightLabel;

    glm::vec3 resultat;

};

#endif // RENDERINGWIDGET_H
