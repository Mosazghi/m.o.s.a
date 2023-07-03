import {
  ArgumentsHost,
  Catch,
  ExceptionFilter,
  ForbiddenException,
  HttpException,
} from '@nestjs/common';
import { Response } from 'express';

// Redirecter til login hvis brukeren ikke er autentisert
@Catch(ForbiddenException)
export class ViewAuthFilter implements ExceptionFilter {
  catch(exception: HttpException, host: ArgumentsHost) {
    const ctx = host.switchToHttp();
    const response = ctx.getResponse<Response>();
    const status = exception.getStatus();
    console.log('REDIRECTED!');
    response.status(status).redirect('/');
  }
}
