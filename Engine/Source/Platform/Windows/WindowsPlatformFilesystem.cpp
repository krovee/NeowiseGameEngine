#include <Platform/Windows/WindowsPlatformFilesystem.h>

#if NW_OS(WIN32)

namespace Neowise::Platform::Windows {
	CFileDescriptor::~CFileDescriptor() {
		--_refCount;
		if (_refCount <= 0 && _autoRelease) {
			_fs.release(*this);
		}
	}

	CFileDescriptor::CFileDescriptor(CFS& fs, const CUUID& uuid, int64& refCount, uint size, bool autoRelease)
		: _fs(fs), _uuid(uuid), _size(size), _autoRelease(autoRelease), _refCount(refCount)
	{
	}

	CFileDescriptor::CFileDescriptor(const CFileDescriptor& o)
		: _fs(o._fs), _uuid(o._uuid), _size(o._size), _autoRelease(o._autoRelease), _refCount(++o._refCount)
	{
	}

	void CFS::release(CFileDescriptor& fd)
	{
	}

}

#endif
