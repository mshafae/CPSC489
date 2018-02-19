#ifndef __CPSC489_MODEL_H
#define __CPSC489_MODEL_H

struct MeshUTFJoint {
 STDSTRINGW name;
 uint32 parent;
 real32 position[3];
 real32 m[9];
 matrix4D m_rel;
};

struct MeshUTFKeyFrame {
 uint32 frame;
 real32 translation[3];
 real32 quaternion[4];
 real32 scale[3];
};

struct MeshUTFBoneKeyFrame {
 STDSTRINGW bone;
 uint32 bone_index;
 uint32 minframe;
 uint32 maxframe;
 std::vector<MeshUTFKeyFrame> keyframes;
};

struct MeshUTFAnimationData {
 uint32 frame;
 real32 delta;
 std::unique_ptr<bool[]> keyed;
 std::unique_ptr<std::array<real32, 3>[]> slist;
 std::unique_ptr<std::array<real32, 3>[]> tlist;
 std::unique_ptr<std::array<real32, 4>[]> qlist;
 std::unique_ptr<matrix4D[]> mlist;
};

struct MeshUTFAnimation {
 STDSTRINGW name;
 bool loop;
 uint32 minframe;
 uint32 maxframe;
 real32 duration;
 std::set<uint32> keyset;
 std::map<uint32, size_t> keymap;
 std::vector<MeshUTFBoneKeyFrame> bonelist;
 std::unique_ptr<MeshUTFAnimationData[]> animdata;
};

struct MeshUTFTexture {
 STDSTRINGW semantic;
 uint32 channel;
 STDSTRINGW filename;
};

struct MeshUTFMesh {
 STDSTRINGW name;
 std::vector<MeshUTFTexture> textures;
 uint32 n_verts;
 std::unique_ptr<std::array<real32, 3>[]> position;
 std::unique_ptr<std::array<real32, 3>[]> normal;
 std::unique_ptr<std::array<real32, 2>[]> uvs[2];
 std::unique_ptr<std::array<uint16, 4>[]> bi;
 std::unique_ptr<std::array<real32, 4>[]> bw;
 std::unique_ptr<std::array<real32, 3>[]> colors[2];
 uint32 n_faces;
 std::unique_ptr<uint32[]> facelist;
};

struct MeshUTFDirect3D {
  ID3D11Buffer* vbuffer;
  ID3D11Buffer* ibuffer;
};

class MeshUTF {
  friend class MeshUTFInstance;
 private :
  std::map<STDSTRINGW, uint32> jointmap;
  std::vector<MeshUTFJoint> joints;
  std::vector<MeshUTFAnimation> animations;
  std::vector<MeshUTFMesh> meshes;
 private :
  std::unique_ptr<MeshUTFDirect3D[]> buffers;
  ID3D11Buffer* ja_buffer;
 private :
  ErrorCode ConstructAnimationData(void);
 public :
  ErrorCode LoadModel(const wchar_t* filename);
  void FreeModel(void);
 public :
  ErrorCode RenderSkeleton(void);
  ErrorCode RenderMeshList(void);
  ErrorCode RenderModel(void);
 public : 
  MeshUTF();
  virtual ~MeshUTF();
 private :
  MeshUTF(const MeshUTF&) = delete;
  void operator =(const MeshUTF&) = delete;  
};

class MeshUTFInstance {
 private :
  static const uint32 FRAMES_PER_SECOND = 30;
  const MeshUTF* mesh;
  real32 time;
  uint32 anim;
 private :
  DirectX::XMMATRIX mv;
  std::unique_ptr<DirectX::XMMATRIX[]> jm;
 private :
  ID3D11Buffer* permodel;
  ID3D11Buffer* perframe;
 public :
  ErrorCode InitInstance(void);
  void FreeInstance(void);
 public :
  uint32 GetAnimation(void)const { return anim; }
  real32 GetTime(void)const { return time; }
 public :
  bool SetAnimation(uint32 index);
  bool SetTime(real32 value);
  bool ResetAnimation(void);
  bool Update(void);
  bool Update(real32 dt);
 public :
  ErrorCode RenderModel(void);
 public :
  MeshUTFInstance(const MeshUTF& ptr);
 ~MeshUTFInstance();
 private :
  MeshUTFInstance(const MeshUTFInstance&) = delete;
  void operator =(const MeshUTFInstance&) = delete;
};

#endif