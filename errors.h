#ifndef __CPSC489_ERRORS_H
#define __CPSC489_ERRORS_H

enum ErrorCode {
 // Common Errors
 EC_SUCCESS = 0,
 EC_FILE_OPEN,
 EC_FILE_SEEK,
 EC_FILE_READ,
 EC_FILE_WRITE,
 EC_FILE_EOF,
 EC_FILE_PARSE,
 EC_FILE_PATHNAME,
 EC_FILE_FILENAME,
 EC_FILE_EXTENSION,
 EC_INVALID_ARG,
 // Windows Errors
 EC_WIN32_REGISTER_WINDOW,
 EC_WIN32_MAIN_WINDOW,
 // Image Errors
 EC_IMAGE_FORMAT,
 EC_BMP_INVALID,
 EC_BMP_COMPRESSED,
 EC_BMP_OPTIMIZED,
 EC_PNG_COM_INIT,
 EC_PNG_DECODER,
 EC_PNG_FILE_OPEN,
 EC_PNG_DECODER_INIT,
 EC_PNG_NO_FRAMES,
 EC_PNG_GET_FRAMES,
 EC_PNG_CONVERTER,
 EC_PNG_CONVERTER_INIT,
 EC_PNG_GET_SIZE,
 EC_PNG_COPY,
 EC_TGA_IMAGE_TYPE_UNSUPPORTED,
 EC_TGA_PIXEL_DEPTH_UNSUPPORTED,
 EC_TGA_PIXEL_DEPTH,
 EC_TGA_MISSING_COLOR_MAP,
 // Direct3D: General Errors
 EC_D3D_CREATE_DEVICE,
 EC_D3D_DEVICE,
 EC_D3D_DEVICE_CONTEXT,
 EC_D3D_GET_BACKBUFFER,
 EC_D3D_CREATE_RENDER_TARGET_VIEW,
 EC_D3D_CREATE_SHADER_RESOURCE,
 EC_D3D_INSERT_SHADER_RESOURCE,
 EC_D3D_SHADER_RESOURCE_REFERENCE_COUNT,
 EC_D3D_SHADER_RESOURCE,
 EC_D3D_CREATE_TEXTURE2D,
 EC_D3D_TEXTURE_DIMENSIONS,
 EC_D3D_CREATE_DEPTH_STENCIL_VIEW,
 EC_D3D_RESIZE_BUFFERS,
 EC_D3D_SET_INPUT_LAYOUT,
 EC_D3D_CREATE_BUFFER,
 EC_D3D_MAP_RESOURCE,
 // Direct3D: Rasterizer State Errors
 EC_D3D_CREATE_RASTERIZER_STATE,
 EC_D3D_RASTERIZER_STATE,
 // Direct3D: Input Layout Errors
 EC_D3D_INPUT_LAYOUT_INDEX,
 EC_D3D_INPUT_LAYOUT_SHADER_LOOKUP,
 EC_D3D_INPUT_LAYOUT_SHADER_SIGNATURE,
 EC_D3D_CREATE_INPUT_LAYOUT,
 // Direct3D: Shader Errors
 EC_D3D_VERTEX_SHADER_FILE_NOT_FOUND,
 EC_D3D_VERTEX_SHADER_FILE_INVALID,
 EC_D3D_CREATE_VERTEX_SHADER,
 EC_D3D_SET_VERTEX_SHADER,
 EC_D3D_PIXEL_SHADER_FILE_NOT_FOUND,
 EC_D3D_PIXEL_SHADER_FILE_INVALID,
 EC_D3D_CREATE_PIXEL_SHADER,
 EC_D3D_SET_PIXEL_SHADER,
 // Model Errors
 EC_MODEL_BONENAME,
 EC_MODEL_BONE_LOOKUP,
 EC_MODEL_ANIMATION_NAME,
 EC_MODEL_KEYFRAMED_BONES,
 EC_MODEL_KEYFRAMES,
 EC_MODEL_MESH,
 EC_MODEL_MESHNAME,
 EC_MODEL_VERTICES,
 EC_MODEL_UV_CHANNELS,
 EC_MODEL_COLOR_CHANNELS,
 EC_MODEL_TEXTURES,
 EC_MODEL_TEXTURE_SEMANTIC,
 EC_MODEL_TEXTURE_CHANNEL,
 EC_MODEL_TEXTURE_FILENAME,
 // Animation Errors
 EC_ANIM_INDEX,
};

enum LanguageCode {
 LC_ENGLISH = 0,
};

// error string functions
void InitErrorStrings(void);
void FreeErrorStrings(void);
STDSTRINGW FindError(ErrorCode code, LanguageCode language = LC_ENGLISH);
inline ErrorCode Success(void) { return EC_SUCCESS; }
inline bool Fail(const ErrorCode& code) { return (code != EC_SUCCESS); }
bool Error(ErrorCode code);
bool Error(ErrorCode code, LanguageCode language);
bool Error(ErrorCode code, LanguageCode language);
ErrorCode DebugErrorCode(ErrorCode code, int line, const char* file);
ErrorCode DebugErrorCode(ErrorCode code, int line, const char* file, LanguageCode language);

// language code functions
LanguageCode GetLanguageCode(void);
void SetLanguageCode(LanguageCode code);

#endif
