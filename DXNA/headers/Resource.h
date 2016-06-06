#pragma once

class Resource 
{
	private:
		const char* filename;
		bool valid = false;

	protected:
		virtual bool load() = 0;
		virtual void release() = 0;

	public:
		int counter;
		inline Resource(const char* file) : filename(file), valid(false), counter(0) {}
		inline const char* getFilename() { return filename; }
		inline bool isValid() { return valid; }
		inline bool Load()
		{
			bool l = load();
			if (l) valid = true;
			return l;
		}
		inline void Release() { release(); valid = false; }
		virtual void* getResource() = 0;
};