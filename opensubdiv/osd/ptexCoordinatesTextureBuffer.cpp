//
//     Copyright (C) Pixar. All rights reserved.
//
//     This license governs use of the accompanying software. If you
//     use the software, you accept this license. If you do not accept
//     the license, do not use the software.
//
//     1. Definitions
//     The terms "reproduce," "reproduction," "derivative works," and
//     "distribution" have the same meaning here as under U.S.
//     copyright law.  A "contribution" is the original software, or
//     any additions or changes to the software.
//     A "contributor" is any person or entity that distributes its
//     contribution under this license.
//     "Licensed patents" are a contributor's patent claims that read
//     directly on its contribution.
//
//     2. Grant of Rights
//     (A) Copyright Grant- Subject to the terms of this license,
//     including the license conditions and limitations in section 3,
//     each contributor grants you a non-exclusive, worldwide,
//     royalty-free copyright license to reproduce its contribution,
//     prepare derivative works of its contribution, and distribute
//     its contribution or any derivative works that you create.
//     (B) Patent Grant- Subject to the terms of this license,
//     including the license conditions and limitations in section 3,
//     each contributor grants you a non-exclusive, worldwide,
//     royalty-free license under its licensed patents to make, have
//     made, use, sell, offer for sale, import, and/or otherwise
//     dispose of its contribution in the software or derivative works
//     of the contribution in the software.
//
//     3. Conditions and Limitations
//     (A) No Trademark License- This license does not grant you
//     rights to use any contributor's name, logo, or trademarks.
//     (B) If you bring a patent claim against any contributor over
//     patents that you claim are infringed by the software, your
//     patent license from such contributor to the software ends
//     automatically.
//     (C) If you distribute any portion of the software, you must
//     retain all copyright, patent, trademark, and attribution
//     notices that are present in the software.
//     (D) If you distribute any portion of the software in source
//     code form, you may do so only under this license by including a
//     complete copy of this license with your distribution. If you
//     distribute any portion of the software in compiled or object
//     code form, you may only do so under a license that complies
//     with this license.
//     (E) The software is licensed "as-is." You bear the risk of
//     using it. The contributors give no express warranties,
//     guarantees or conditions. You may have additional consumer
//     rights under your local laws which this license cannot change.
//     To the extent permitted under your local laws, the contributors
//     exclude the implied warranties of merchantability, fitness for
//     a particular purpose and non-infringement.
//
#include "../version.h"

#if not defined(__APPLE__)
    #include <GL/glew.h>
#else
    #include <OpenGL/gl3.h>
#endif

#include "../far/mesh.h"
#include "../osd/ptexCoordinatesTextureBuffer.h"

namespace OpenSubdiv {
namespace OPENSUBDIV_VERSION {

OsdPtexCoordinatesTextureBuffer::OsdPtexCoordinatesTextureBuffer(FarMesh<OsdVertex> *farMesh, int level) {

    const std::vector<int> &ptexCoordinates = farMesh->GetPtexCoordinates(level);

    // creates buffer even if the ptexCoordinates is empty.
    int size = (int)ptexCoordinates.size() * sizeof(GLint);
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_TEXTURE_BUFFER, buffer);
    glBufferData(GL_TEXTURE_BUFFER, size, &(ptexCoordinates[0]), GL_STATIC_DRAW);
    
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_BUFFER, _texture);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RG32I, buffer);
    glDeleteBuffers(1, &buffer);
    glBindTexture(GL_TEXTURE_BUFFER, 0);
}

OsdPtexCoordinatesTextureBuffer::~OsdPtexCoordinatesTextureBuffer() {

    glDeleteTextures(1, &_texture);
}

GLuint
OsdPtexCoordinatesTextureBuffer::GetGlTexture() const {

    return _texture;
}


} // end namespace OPENSUBDIV_VERSION
} // end namespace OpenSubdiv