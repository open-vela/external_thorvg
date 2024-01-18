/*
 * Copyright (c) 2023 - 2024 the ThorVG project. All rights reserved.

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _TVG_WG_BIND_GROUPS_H_
#define _TVG_WG_BIND_GROUPS_H_

#include "tvgWgCommon.h"
#include "tvgWgShaderTypes.h"

// @group(0)
struct WgBindGroupCanvas : public WgBindGroup
{
    static WGPUBindGroupLayout layout;
    static WGPUBindGroupLayout getLayout(WGPUDevice device);
    static void releaseLayout();

    WGPUBuffer uBufferViewMat{};
    void initialize(WGPUDevice device, WGPUQueue queue,
                    WgShaderTypeMat4x4f& uViewMat);
    void release();
};


// @group(1)
struct WgBindGroupPaint : public WgBindGroup
{
    static WGPUBindGroupLayout layout;
    static WGPUBindGroupLayout getLayout(WGPUDevice device);
    static void releaseLayout();

    WGPUBuffer uBufferModelMat{};
    WGPUBuffer uBufferBlendSettings{};
    void initialize(WGPUDevice device, WGPUQueue queue,
                    WgShaderTypeMat4x4f&       uModelMat,
                    WgShaderTypeBlendSettings& uBlendSettings);
    void release();
};

// @group(2)
struct WgBindGroupSolidColor : public  WgBindGroup
{
    static WGPUBindGroupLayout layout;
    static WGPUBindGroupLayout getLayout(WGPUDevice device);
    static void releaseLayout();

    WGPUBuffer uBufferSolidColor{};
    void initialize(WGPUDevice device, WGPUQueue queue,
                    WgShaderTypeSolidColor &uSolidColor);
    void release();
};

// @group(2)
struct WgBindGroupLinearGradient : public  WgBindGroup
{
    static WGPUBindGroupLayout layout;
    static WGPUBindGroupLayout getLayout(WGPUDevice device);
    static void releaseLayout();

    WGPUBuffer uBufferLinearGradient{};
    void initialize(WGPUDevice device, WGPUQueue queue,
                    WgShaderTypeLinearGradient &uLinearGradient);
    void release();
};

// @group(2)
struct WgBindGroupRadialGradient : public  WgBindGroup
{
    static WGPUBindGroupLayout layout;
    static WGPUBindGroupLayout getLayout(WGPUDevice device);
    static void releaseLayout();

    WGPUBuffer uBufferRadialGradient{};
    void initialize(WGPUDevice device, WGPUQueue queue,
                    WgShaderTypeRadialGradient &uRadialGradient);
    void release();
};

// @group(2)
struct WgBindGroupPicture : public  WgBindGroup
{
    static WGPUBindGroupLayout layout;
    static WGPUBindGroupLayout getLayout(WGPUDevice device);
    static void releaseLayout();

    void initialize(WGPUDevice device, WGPUQueue queue,
                    WGPUSampler     uSampler,
                    WGPUTextureView uTextureView);
    void release();
};

// @group(1 or 2)
struct WgBindGroupOpacity : public  WgBindGroup
{
    static WGPUBindGroupLayout layout;
    static WGPUBindGroupLayout getLayout(WGPUDevice device);
    static void releaseLayout();

    WGPUBuffer uBufferOpacity{};
    void initialize(WGPUDevice device, WGPUQueue queue, uint32_t uOpacity);
    void update(WGPUDevice device, WGPUQueue queue, uint32_t uOpacity);
    void release();
};

// @group(0 or 1)
struct WgBindGroupBlit : public  WgBindGroup
{
    static WGPUBindGroupLayout layout;
    static WGPUBindGroupLayout getLayout(WGPUDevice device);
    static void releaseLayout();

    void initialize(WGPUDevice device, WGPUQueue queue,
                    WGPUSampler     uSampler,
                    WGPUTextureView uTexture);
    void release();
};

//************************************************************************
// bind group pools
//************************************************************************

class WgBindGroupOpacityPool
{
private:
    Array<WgBindGroupOpacity*> mList;
    Array<WgBindGroupOpacity*> mPool;
    Array<WgBindGroupOpacity*> mUsed;
public:
    WgBindGroupOpacity* allocate(WgContext& context, uint32_t opacity);
    void reset();
    void release();
};

#endif // _TVG_WG_BIND_GROUPS_H_
