/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrCCQuadraticShader_DEFINED
#define GrCCQuadraticShader_DEFINED

#include "ccpr/GrCCCoverageProcessor.h"

/**
 * This class renders the coverage of closed quadratic curves using the techniques outlined in
 * "Resolution Independent Curve Rendering using Programmable Graphics Hardware" by Charles Loop and
 * Jim Blinn:
 *
 * https://www.microsoft.com/en-us/research/wp-content/uploads/2005/01/p1000-loop.pdf
 *
 * The provided curves must be monotonic with respect to the vector of their closing edge [P2 - P0].
 * (Use GrCCGeometry::quadraticTo().)
 */
class GrCCQuadraticShader : public GrCCCoverageProcessor::Shader {
protected:
    void emitSetupCode(GrGLSLVertexGeoBuilder*, const char* pts, const char* wind,
                       const char** tighterHull) const override;

    void onEmitVaryings(GrGLSLVaryingHandler*, GrGLSLVarying::Scope, SkString* code,
                        const char* position, const char* coverage,
                        const char* attenuatedCoverage) override;

    void onEmitFragmentCode(GrGLSLFPFragmentBuilder*, const char* outputCoverage) const override;

    const GrShaderVar fQCoordMatrix{"qcoord_matrix", kFloat2x2_GrSLType};
    const GrShaderVar fQCoord0{"qcoord0", kFloat2_GrSLType};
    const GrShaderVar fEdgeDistanceEquation{"edge_distance_equation", kFloat3_GrSLType};
    GrGLSLVarying fCoord;
    GrGLSLVarying fCoverages;
};

#endif
