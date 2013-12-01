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
#include <typeinfo>

class Variant
{
public:
	Variant() { }

	template<class T>
	Variant(T val) :
		mImpl(new VariantImpl<T>(val))
	{
	}

	template<class T>
	T& getValue()
	{
		return dynamic_cast<VariantImpl<T>&> (*mImpl).mValue;
	}

	template<class T>
	void setValue(const T& inValue)
	{
		mImpl.reset(new VariantImpl<T>(inValue));
	}

private:
	struct AbstractVariantImpl
	{
		virtual ~AbstractVariantImpl() { }
	};

	template<class T>
	struct VariantImpl : public AbstractVariantImpl
	{
		VariantImpl(T val) : mValue(val) { }
		~VariantImpl() { }
		T mValue;
	};

	std::shared_ptr<AbstractVariantImpl> mImpl;
};

#endif // _VARIANT_H_

