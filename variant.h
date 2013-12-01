/* Copyright (c) 2013 Richard Russon (FlatCap)
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef _VARIANT_H_
#define _VARIANT_H_

#include <memory>

template <typename T>
struct TypeWrapper
{
	typedef T TYPE;
	typedef T& REFTYPE;
};

class Variant
{
public:
	Variant() { }

	template<class T>
	Variant(T inValue) :
		mImpl(new VariantImpl<typename TypeWrapper<T>::TYPE>(inValue))
	{
	}

	template<class T>
	typename TypeWrapper<T>::REFTYPE getValue()
	{
		return dynamic_cast<VariantImpl<typename TypeWrapper<T>::TYPE>&>(*mImpl.get()).mValue;
	}

private:
	struct AbstractVariantImpl
	{
		virtual ~AbstractVariantImpl() {}
	};

	template<class T>
	struct VariantImpl : public AbstractVariantImpl
	{
		VariantImpl(T inValue) :
			mValue(inValue)
		{
		}

		~VariantImpl() {}

		T mValue;
	};

	std::shared_ptr<AbstractVariantImpl> mImpl;
};

#endif // _VARIANT_H_

