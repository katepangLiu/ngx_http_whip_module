#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

typedef struct {
	ngx_uint_t whip_version;
} ngx_http_whip_loc_conf_t;

static void *ngx_http_whip_create_loc_conf(ngx_conf_t *cf);
static char *ngx_http_whip_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child);

static ngx_http_module_t  ngx_http_whip_module_ctx = {
	NULL,								/* preconfiguration */
	NULL,								/* postconfiguration */

	NULL,								/* create main configuration */
	NULL,								/* init main configuration */

	NULL,								/* create server configuration */
	NULL,								/* merge server configuration */

	ngx_http_whip_create_loc_conf,		/* create location configuration */
	ngx_http_whip_merge_loc_conf		/* merge location configuration */
};

static ngx_int_t ngx_http_whip_handler(ngx_http_request_t *r);
static char *ngx_http_webrtc_ingestion(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);

static ngx_command_t ngx_http_whip_commands[] = {
	{	ngx_string("webrtc_ingestion"),
		NGX_HTTP_LOC_CONF|NGX_HTTP_LIF_CONF|NGX_HTTP_LMT_CONF|NGX_CONF_TAKE1,
		ngx_http_webrtc_ingestion,
		NGX_HTTP_LOC_CONF_OFFSET,
		0,
		NULL},
	}
};

ngx_module_t  ngx_http_whip_module = {
	NGX_MODULE_V1,
	&ngx_http_whip_module_ctx,			/* module context */
	ngx_http_whip_commands,			   /* module directives */
	NGX_HTTP_MODULE,					   /* module type */
	NULL,								  /* init master */
	NULL,								  /* init module */
	NULL,								  /* init process */
	NULL,								  /* init thread */
	NULL,								  /* exit thread */
	NULL,								  /* exit process */
	NULL,								  /* exit master */
	NGX_MODULE_V1_PADDING
};

static void* ngx_http_whip_create_loc_conf(ngx_conf_t *cf) {
	ngx_http_whip_loc_conf_t* plcf;
	return conf;
}

static void* ngx_http_whip_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child) {
	ngx_http_proxy_loc_conf_t *prev = parent;
	ngx_http_proxy_loc_conf_t *conf = child;
	
	return NGX_CONF_OK;
}

static ngx_int_t ngx_http_whip_handler(ngx_http_request_t *r) {
	return NGX_DONE;
}

static char *ngx_http_webrtc_ingestion(ngx_conf_t *cf, ngx_command_t *cmd, void *conf) {
	ngx_http_whip_loc_conf_t* plcf = conf;
	ngx_http_core_loc_conf_t* clcf;
	
	clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
	clcf->handler = ngx_http_whip_handler;
	return NGX_DONE;
}