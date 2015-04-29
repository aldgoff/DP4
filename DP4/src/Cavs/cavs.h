/*
 * cavs.h
 *
 *  Created on: Apr 27, 2015
 *      Author: aldgoff
 *
 * Description:
 *   Place to try out code for learning cAVS and its maestro implementation.
 */

#ifndef DP4_SRC_CAVS_H_
#define DP4_SRC_CAVS_H_

namespace cavs {

class Device {};
class SubDevice : public Device {};
class PmDevice : public Device {};
class CAVS : public PmDevice {};

class RegInfo {};

namespace fw {

class Comms {
public: virtual ~Comms() {}
	virtual void ReadReg(RegInfo& reginfo) {}
	virtual void WriteReg(RegInfo& reginfo) {}
	virtual void ReadMem() {}
	virtual void WriteMem() {}
};

}//fw

namespace production_fw {

using namespace fw;

class CoeFwAdapter : public Comms {
public:
	CoeFwAdapter() {}
public:
	void ReadReg() {}
	void WriteReg() {}
	void ReadMem32() {}
	void WriteMem32() {}
};

}//production_fw

namespace engine_fw {

using namespace fw;

class CommsAdapter : public Comms {
	int	m_buff;
public:
	CommsAdapter() : m_buff(0) {}
	virtual ~CommsAdapter() {}
public:
	virtual void RecvMessage() {}
	//...
public:
	unsigned GetMsgSizeInBytes() {
		unsigned size_B = 4;
		return size_B;
	}
	//...
};

}//engine_fw

namespace try_c_plus_plus {

struct Allocator {
	virtual int Get(int x)=0;	// undefined reference to `cavs::try_c_plus_plus::Allocator::Get(int)'
};
class Simple : public Allocator {
public: virtual ~Simple() {}
	virtual int Get(int x) {
		return 2*x;
	}
};

//int Allocator::Get(int x) { return 3; }

}

void demo() {
	cout << "<< exploration >>\n";

	using namespace try_c_plus_plus;
	Allocator* poly = new Simple;
	cout << "  Get = " << poly->Get(5) << ".\n";

	cout << endl;
}

}//cavs



#endif /* DP4_SRC_CAVS_H_ */
