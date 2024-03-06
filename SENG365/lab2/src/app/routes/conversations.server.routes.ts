import {Express} from "express";
import * as convos from '../controllers/conversations.server.controller';

module.exports = ( app: Express ) => {

    app.route( '/api/conversations' )
        .get( convos.list )
        .post( convos.create );

    app.route( '/api/conversations/:id' )
        .get( convos.read )
        .put( convos.update )
        .delete( convos.remove );
};