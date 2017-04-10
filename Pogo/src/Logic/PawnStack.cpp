#include <Logic/PawnStack.hpp>

std::ostream& operator<<(std::ostream& os, const PawnStack& pawnStack) {
	os << "[";
	for(unsigned int i = PawnStack::max_size(); --i;) {
		os << ((pawnStack.m_stack >> i) & 1);
	}
	os << (pawnStack.m_stack & 1) << "]";
	return os;
}

PawnStack::PawnStack(const uint8_t stack) : m_stack(stack) {
	if(!stack) {
		SLOG_ERR("Empty stack: no end byte");
	}
}

unsigned int PawnStack::size() const {
	for(unsigned int i = max_size(); --i;) {
		if(m_stack >> i == 1) {
			return i;
		}
	}
	return 0;
}

constexpr unsigned int PawnStack::max_size() {
	return sizeof(m_stack) * 8;
}

PawnStack PawnStack::pick(const unsigned int number) {
	unsigned int currentSize = size();
	uint8_t stack = static_cast<uint8_t>(m_stack >> (size() - number));
	m_stack = static_cast<uint8_t>(m_stack & (0b11111111 >> (max_size() - currentSize + number)));
	m_stack = static_cast<uint8_t>(m_stack | (1 << (currentSize - number)));
	return PawnStack(stack);
}

void PawnStack::add(const PawnStack pawnStack) {
	unsigned int currentSize = size();
	unsigned int addedSize = pawnStack.size();
	if(currentSize + addedSize > PawnStack::max_size() - 1) {
		SLOG_ERR("new size bigger than max size");
	}
	m_stack = static_cast<uint8_t>(m_stack & (0b11111111 >> (PawnStack::max_size() - currentSize)));
	m_stack = static_cast<uint8_t>(m_stack | (pawnStack.m_stack << currentSize));
}
