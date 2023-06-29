import { CanActivate, ExecutionContext, Injectable } from '@nestjs/common';

// Authentiseringsstrategi for Passport (bruker LocalStrategy)

@Injectable()
export class AuthenticatedGuard implements CanActivate {
  async canActivate(context: ExecutionContext) {
    const req = context.switchToHttp().getRequest();

    return req.isAuthenticated();
  }
}
