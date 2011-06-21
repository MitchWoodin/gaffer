//////////////////////////////////////////////////////////////////////////
//  
//  Copyright (c) 2011, Image Engine Design Inc. All rights reserved.
//  
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are
//  met:
//  
//      * Redistributions of source code must retain the above
//        copyright notice, this list of conditions and the following
//        disclaimer.
//  
//      * Redistributions in binary form must reproduce the above
//        copyright notice, this list of conditions and the following
//        disclaimer in the documentation and/or other materials provided with
//        the distribution.
//  
//      * Neither the name of John Haddon nor the names of
//        any other contributors to this software may be used to endorse or
//        promote products derived from this software without specific prior
//        written permission.
//  
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
//  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
//  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
//  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  
//////////////////////////////////////////////////////////////////////////

#include "IECore/VectorTypedParameter.h"

#include "Gaffer/VectorTypedParameterHandler.h"

using namespace Gaffer;

template<typename T>
ParameterHandler::ParameterHandlerDescription<VectorTypedParameterHandler<T>, IECore::TypedParameter<std::vector<T> > > VectorTypedParameterHandler<T>::g_description;

template<typename T>
VectorTypedParameterHandler<T>::VectorTypedParameterHandler( typename ParameterType::Ptr parameter, GraphComponentPtr plugParent )
	:	ParameterHandler( parameter )
{
	m_plug = plugParent->getChild<PlugType>( parameter->name() );
	if( !m_plug )
	{
		m_plug = new PlugType( parameter->name(), Plug::In, static_cast<const DataType *>( parameter->defaultValue() ) );
	}
	plugParent->addChild( m_plug );
}

template<typename T>
VectorTypedParameterHandler<T>::~VectorTypedParameterHandler()
{
}
		
template<typename T>
void VectorTypedParameterHandler<T>::setParameterValue()
{
	ParameterType *p = static_cast<ParameterType *>( parameter().get() );
	p->setValue( m_plug->getValue()->copy() );
}

template<typename T>
void VectorTypedParameterHandler<T>::setPlugValue()
{
	const ParameterType *p = static_cast<ParameterType *>( parameter().get() );
	m_plug->setValue( static_cast<const DataType *>( p->getValue() ) );
}
		
// explicit instantiations

template class VectorTypedParameterHandler<int>;
template class VectorTypedParameterHandler<float>;
template class VectorTypedParameterHandler<std::string>;
template class VectorTypedParameterHandler<Imath::V3f>;
