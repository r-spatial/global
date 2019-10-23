#include "Rcpp.h"

#include <s2/s2point.h>
#include <s2/s2loop.h>
#include <s2/s2polygon.h>
#include <s2/s2builder.h>

// [[Rcpp::export]]
int s2io(Rcpp::NumericMatrix cc) {
	int i;
}

// [[Rcpp::export]]
Rcpp::NumericVector area_loops_from_list(Rcpp::List l) {

  S2Polygon* polygon = new S2Polygon;
  std::vector<std::unique_ptr<S2Loop>> loops;
  for (int li = 0; li < l.size(); ++li) {
    std::vector<S2Point> vertices;
	Rcpp::NumericMatrix m = l[li];
    for (int vi = 0; vi < (m.nrow() - 1); ++vi) {
      // Rcpp::Rcout << vi << m[vi,0]/le << m[vi,1]/le << m[vi,2]/le << std::endl;
      // Rcpp::Rcout << vi << " " << m(vi,0) << " " << m(vi,1) << " " << m(vi,2) << std::endl;
	  double le = sqrt(pow(m(vi,0),2) + pow(m(vi,1),2) + pow(m(vi,2),2));
      S2Point p(m(vi,0)/le, m(vi,1)/le, m(vi,2)/le); 
      vertices.push_back(p);
    }
    loops.push_back(absl::make_unique<S2Loop>(vertices));
  }
  polygon->InitNested(std::move(loops));
  Rcpp::NumericVector v(1);
  v[0] = polygon->GetArea();
  return v;
}

/*
S2Loop get_loop(Rcpp::NumericMatrix v) {
	if (v.ncol() != 3)
		Rcpp::stop("v does not have 3 columns");
	std::vector<S2Point> vertices(v.nrow());
	for (size_t i = 0; i < v.nrow(); i++)
		vertices[i] = S2Point(v[i,0], v[i,1], v[i,2]);
	S2Loop s; 
	s.Init(vertices);
	return s;
}

std::vector<std::unique_ptr<S2Loop> > get_loops(Rcpp::List polygons) {
	// create vector of loops
	std::vector<std::unique_ptr<S2Loop> > ret(polygons.size());
	for (size_t i; i < polygons.size(); i++) {
		Rcpp::NumericMatrix m = polygons[i];
		loop = get_loop(m);
		loop_vec.push_back(std::unique_ptr<S2Loop>(loop));
	}
	return(loop_vec)
}

// [[Rcpp::export]]
S2Polygon *add_polygons(Rcpp::List sf_polygons)
{
	using s2builderutil::IntLatLngSnapFunction;
	S2Builder builder(S2Builder::Options(IntLatLngSnapFunction(7)));
	S2Polygon output;
	builder.StartLayer(absl::make_unique<s2builderutil::S2PolygonLayer>(&output));
	// Create polygon input
	S2Polygon* polygon = new S2Polygon;
	polygon.InitOriented(get_loops(sf_polygons));
	// ::DISABLE to turn off verification
	builder.AddPolygon(polygon); // assumes directed: CCW exterior, CW holes
	S2Error error;
	if (!builder.Build(&error)) {
	  S2_LOG(ERROR) << error;
	  // ...
	}
	return polygon;
}

*/
