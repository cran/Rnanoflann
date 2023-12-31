#[export]
nn <- function(data, points, k = nrow(data), method = "euclidean", search = "standard", 
eps = 0.0, square = FALSE, sorted = FALSE, radius = 0.0, trans = TRUE, leafs = 10L, p = 0.0, parallel = FALSE, cores = 0L) {
    if(method == "hellinger"){
		data <- sqrt(data)
		points <- sqrt(points)
	}
    res <- .Call(`_Rnanoflann_nn`, t(data), t(points), k, method, search, eps, square, sorted, radius, leafs, p, parallel, cores)
    if(trans){
        res$indices <- t(res$indices)
        res$distances <- t(res$distances)
    }
    res
}