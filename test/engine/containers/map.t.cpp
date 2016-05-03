// map.t.cpp
#include <engine/containers/map.h>
#include <gtest/gtest.h>
#include <engine/memory/counting_allocator.h>

namespace
{

nge::cntr::DynamicArray<nge::String>
getKeys( nge::mem::IAllocator<nge::String>* allocator )
{
    using namespace nge::cntr;
    using namespace nge::mem;
    using namespace nge;

    DynamicArray<String> arr( allocator );

    int32 i;
    int32 j;
    for ( i = 0; i < 2048; ++i )
    {
        std::ostringstream oss;
        for ( j = 0; j <= i; ++j )
        {
            oss << String( "a" );
        }

        arr.push( oss.str() );
    }

    return arr;
}

nge::uint32 hashFunc( const nge::String& value )
{
    return static_cast<nge::uint32>( value.size() );
}

} // End nspc anonymous

TEST( Map, Construction )
{
    using namespace nge::cntr;
    using namespace nge::mem;
    using namespace nge;

    CountingAllocator<Map<String, String>::Pair> pairAlloc;
    CountingAllocator<uint32> intAlloc;
    std::function<uint32( const String& )> func( &hashFunc );

    Map<String, String> map1();
    Map<String, String> map2( func );
    Map<String, String> map3( 3000 );
    Map<String, String> map4( &pairAlloc, &intAlloc );
    Map<String, String> map5( &pairAlloc, &intAlloc, 3000 );
    Map<String, String> map6( &pairAlloc, &intAlloc, func );
    Map<String, String> map7( &pairAlloc, &intAlloc, 3000, func );

    Map<String, String> copyMap( map7 );
    Map<String, String> moveMap( std::move( map7 ) );
}

TEST( Map, CopyAndMove )
{
    using namespace nge::cntr;
    using namespace nge::mem;
    using namespace nge;

    DefaultAllocator<String> alloc;
    CountingAllocator<Map<String, String>::Pair> pairAlloc;
    CountingAllocator<uint32> binAlloc;

    Map<String, String> map( &pairAlloc, &binAlloc );
    DynamicArray<String> keys = getKeys( &alloc );

    uint32 i;
    for ( i = 0; i < keys.size(); ++i )
    {
        map[keys[i]] = keys[i];
    }

    Map<String, String> copy( map );
    for ( i = 0; i < keys.size(); ++i )
    {
        ASSERT_STREQ( keys[i].c_str(), copy[keys[i]].c_str() );
    }

    Map<String, String> moved( std::move( copy ) );
    for ( i = 0; i < keys.size(); ++i )
    {
        ASSERT_STREQ( keys[i].c_str(), moved[keys[i]].c_str() );
    }

    ASSERT_EQ( 0, copy.size() );
    ASSERT_NE( 0, map.size() );
    ASSERT_TRUE( copy.isEmpty() );
    ASSERT_FALSE( map.isEmpty() );
}

TEST( Map, InsertionAndRemoval )
{
    using namespace nge::cntr;
    using namespace nge::mem;
    using namespace nge;

    DefaultAllocator<String> alloc;
    CountingAllocator<Map<String, String>::Pair> pairAlloc;
    CountingAllocator<uint32> binAlloc;

    Map<String, String> map( &pairAlloc, &binAlloc );
    DynamicArray<String> keys = getKeys( &alloc );

    uint32 i;
    for ( i = 0; i < keys.size(); ++i )
    {
        map[keys[i]] = keys[i];
        ASSERT_STREQ( keys[i].c_str(), map[keys[i]].c_str() );
        ASSERT_TRUE( map.has( keys[i] ) );
    }

    for ( i = 0; i < keys.size(); ++i )
    {
        ASSERT_STREQ( keys[i].c_str(), map.remove( keys[i] ).c_str() );
    }

    for ( i = 0; i < keys.size(); ++i )
    {
        map.put( keys[i], keys[i] );
        ASSERT_STREQ( keys[i].c_str(), map[keys[i]].c_str() );
    }

    map.clear();

    for ( i = 0; i < keys.size(); ++i )
    {
        String key = keys[i];
        map.put( keys[i], std::move( key ) );
        ASSERT_STREQ( keys[i].c_str(), map[keys[i]].c_str() );
        ASSERT_STRNE( key.c_str(), map[keys[i]].c_str() );
    }

    map.clear();

    ASSERT_EQ( 0, map.size() );
    ASSERT_TRUE( map.isEmpty() );

    for ( i = 0; i < keys.size(); ++i )
    {
        map[keys[i]] = keys[i];
        ASSERT_STREQ( keys[i].c_str(), map[keys[i]].c_str() );
        ASSERT_TRUE( map.has( keys[i] ) );
    }

    for ( i = 0; i < keys.size(); ++i )
    {
        ASSERT_STREQ( keys[i].c_str(), map.remove( keys[i] ).c_str() );
    }

    for ( i = 0; i < keys.size(); ++i )
    {
        map.put( keys[i], keys[i] );
        ASSERT_STREQ( keys[i].c_str(), map[keys[i]].c_str() );
    }

    map.clear();

    for ( i = 0; i < keys.size(); ++i )
    {
        String key = keys[i];
        map.put( keys[i], std::move( key ) );
        ASSERT_STREQ( keys[i].c_str(), map[keys[i]].c_str() );
        ASSERT_STRNE( key.c_str(), map[keys[i]].c_str() );
    }

    map.clear();

    ASSERT_EQ( 0, map.size() );
    ASSERT_TRUE( map.isEmpty() );
}

TEST( Map, Iterator )
{
    using namespace nge::cntr;
    using namespace nge::mem;
    using namespace nge;

    DefaultAllocator<String> alloc;
    CountingAllocator<Map<String, String>::Pair> pairAlloc;
    CountingAllocator<uint32> binAlloc;

    Map<String, String> map( &pairAlloc, &binAlloc );
    DynamicArray<String> keys = getKeys( &alloc );

    uint32 i;
    for ( i = 0; i < keys.size(); ++i )
    {
        map[keys[i]] = keys[i];
    }

    for ( auto iter = map.cbegin(); iter != map.cend(); ++iter )
    {
        ASSERT_STREQ( iter->key.c_str(), iter->value.c_str() );
    }

    auto iter = map.cbegin();
    for ( i = 0; i < map.size(); ++i, ++iter )
    {
        ASSERT_STREQ( keys[i].c_str(), iter->key.c_str() );
        ASSERT_STREQ( keys[i].c_str(), iter->value.c_str() );
    }
}