#pragma once

#include "WindowsBase.h"
#include <Base/UUID.h>
#include <Base/StringView.h>

namespace Neowise::Platform::Windows {
	class CFS;

	/** 
	* 
	*/
	class NW_API CFileDescriptor {
	public:
		~CFileDescriptor();
		CFileDescriptor(CFS& fs, const CUUID& uuid, int64& refCount, uint size, bool autoRelease);

		CFileDescriptor(const CFileDescriptor&);
		CFileDescriptor(CFileDescriptor&&);

		CFileDescriptor& operator=(const CFileDescriptor&) = default;
		CFileDescriptor& operator=(CFileDescriptor&&) = default;

		uint getSize() const;

		uint getData(uint offset, uint size) const;
		uint getData(uint size) const;
		uint getData() const;

	private:
		CFS&	_fs;
		CUUID	_uuid = {};
		uint	_size = {};
		int64&	_refCount;
		bool	_autoRelease = true;
	};

	/** 
	* 
	*/
	class NW_API CFS {
	public:
		CFS();
		~CFS();

		CFileDescriptor create(const CStringView& filepath);
		CFileDescriptor open(const CStringView& filepath);
		CFileDescriptor createOrOpen(const CStringView& filepath);
		void			release(CFileDescriptor& fd);

		void*			read(const CFileDescriptor& fd);
		void*			read(const CFileDescriptor& fd, uint size);
		void*			read(const CFileDescriptor& fd, uint offset, uint size);

		void			write(CFileDescriptor& fd, const void* data, uint size);
		void			write(CFileDescriptor& fd, const void* data, uint offset, uint size);

	private:
		friend class CFileDescriptor;
	private:
		// Hash table holds entries which are contains reference count 
		// of file HANDLE. If int64 value is <= 0, release HANDLE.
		// TODO(krovee): CHashtable<CUUID, CPair<int64, HANDLE> >	_FDs = {};
	};
}
