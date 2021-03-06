#ifndef LIB_FS_INODE_HPP_
#define LIB_FS_INODE_HPP_

#include "file_descriptor.hpp"
#include "dir_descriptor.hpp"

namespace fs
{

class inode
{
public:
	enum class type
	{
		file = 0,
		dir  = 1,
	};

	inode();
	virtual ~inode();
    virtual inode::type get_type() const = 0;
	// Returns the file descriptor, if this inode represents file.
	// Meaningless if used on the dir inode.
	virtual file_ptr open();
	// If this inode is directory, then it returns the descriptor associated
	// with this directory. Meaningless if used on file inode.
	virtual dir_ptr open_dir();
	// Returns size of a file if a type is file
	// or number of entries if the type is dir
	virtual ssize_t size() const = 0;
    // Gets a name of an entity, returns bytes written excluding null character.
    // If truncation occur then it will return amount bytes that would have
    // been written if enough space had been avaliable.
    virtual ssize_t get_name(char *buf, size_t buf_sz) const = 0;
    // Assigns weak reference, so it can pass to descriptors, when they are
    // created using open() and open_dir() methods.
    int set_weak(const fs::inode_ptr &ptr);

    /*
     TODO:
     declare move(), copy(), create() and delete() operations
	 */
protected:
    // Allows to pass this reference to a dir descriptor without increasing
    // a reference counter to prevent cycle dependency.
    fs::inode_weak my_ptr;
};

// TODO: move it somewhere
using inode_ptr = ecl::shared_ptr< inode >;


}

#endif
