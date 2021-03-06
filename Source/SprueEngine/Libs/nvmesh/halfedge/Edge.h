// This code is in the public domain -- castanyo@yahoo.es

#pragma once
#ifndef NV_MESH_HALFEDGE_EDGE_H
#define NV_MESH_HALFEDGE_EDGE_H

#include <SprueEngine/MathGeoLib/AllMath.h>

namespace nv
{
    namespace HalfEdge { class Vertex; class Face; class Edge; }

    /// Half edge edge. 
    class HalfEdge::Edge
    {
        Edge(const Edge&) = delete;
    public:

        unsigned id;

        Edge * next;
        Edge * prev;	// This is not strictly half-edge, but makes algorithms easier and faster.
        Edge * pair;
        Vertex * vertex;
        Face * face;


        // Default constructor.
        Edge(unsigned id) : id(id), next(nullptr), prev(nullptr), pair(nullptr), vertex(nullptr), face(nullptr)
        {
        }


        // Vertex queries.
        const Vertex * from() const { return vertex; }
        Vertex * from() { return vertex; }

        const Vertex * to() const { return pair->vertex; }  // This used to be 'next->vertex', but that changed often when the connectivity of the mesh changes.
        Vertex * to() { return pair->vertex; }

        Edge* circular() { return pair->next; }
        const Edge* circular() const { return pair->next; }


        // Edge queries.
        void setNext(Edge * e) { next = e; if (e != nullptr) e->prev = this; }
        void setPrev(Edge * e) { prev = e; if (e != nullptr) e->next = this; }

        // @@ Add these helpers:
        //Edge * nextBoundary();
        //Edge * prevBoundary();

        // @@ It would be more simple to only check m_pair == NULL
        // Face queries.
        bool isBoundary() const { return !(face && pair->face); }

        // @@ This is not exactly accurate, we should compare the texture coordinates...
        bool isSeam() const { return vertex != pair->next->vertex || next->vertex != pair->vertex; }

        bool isValid() const;

        // Geometric queries.
        SprueEngine::Vec3 midPoint() const;
        float length() const;
        float angle() const;

        float cotangentWeight() const;
    };

} // nv namespace


#endif // NV_MESH_HALFEDGE_EDGE_H
